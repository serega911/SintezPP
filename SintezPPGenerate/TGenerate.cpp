#include "TGenerate.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TReplace.h"
#include <iostream>


void pss::TGenerate::generate()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "====  ������ ����������� ������� � ����� ��������� �������. ���������.  ====\n\n";
	//	�������� ������
	int W;			// RK: Default value
	int N;			// RK: same
	std::cout << "\t\t\t�������� ������." << std::endl << "����� �������� �������:	";
	std::cin >> W;
	std::cout << "���������� ��:		";
	std::cin >> N;
	pss::TSingletons::getInstance()->setGlobalParameters(W, N);
	std::cout << "���������� ������:	"		<< pss::TSingletons::getInstance()->getNumberOfLinks() << std::endl;
	std::cout << "���������� ����������:	"	<< pss::TSingletons::getInstance()->getNumberOfFrictions() << std::endl;
	std::cout << "���������� ��������:	"		<< pss::TSingletons::getInstance()->getNumberOfBrakes() << std::endl;

	//	��������� ������ ���� ��������� ������, ���������� ����� ����� ���������� ������ ���� � ����������� �����.
	m_allLinks.clear();
// 	for (int i = 0; i <= pss::TMainElement::s_numberOfMainElements * (N - 1); i++)
// 	{
// 		for (int j = (i / pss::TMainElement::s_numberOfMainElements + 1) * pss::TMainElement::s_numberOfMainElements; j < pss::TMainElement::s_numberOfMainElements * N; j++)
// 			m_allLinks.push_back(pss::TLink(pss::TElement(i), pss::TElement(j)));
// 	}
	for (int i = 1; i < N; i++)
	{
		for (pss::TMainElement mElem1; mElem1.end(); mElem1++)
		{
			for (int j = i + 1; j <= N; j++)
			{
				for (pss::TMainElement mElem2; mElem2.end(); mElem2++)
				{
					m_allLinks.push_back(pss::TLink(pss::TElement(mElem1,i), pss::TElement(mElem2,j)));
				}
			}
		}
	}

	generateInOut();
}

void pss::TGenerate::generateInOut()
{
	pss::TCode code;
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
// 	for (int in = 0; in < 3 * N; in++)				//	���� �� ��� ������
// 		for (int out = 0; out < 3 * N; out++)		//	����� �� ��� ������
// 		{
// 			if (in != out)							//	��������: ���� � ����� �� ����� ���� ����� � ��� �� ���������
// 			{
// 				code.clear();
// 				code.setIn(pss::TElement(in));
// 				code.setOut(pss::TElement(out));
// 				generateLinks(code);
// 			}
// 		}
	for (int i = 1; i <= N; i++)
	{
		for (pss::TMainElement inElem; inElem.end(); inElem++) // RK: to strange for that i ever seen
		{
			for (int j = 1; j <= N; j++)
			{
				for (pss::TMainElement outElem; outElem.end(); outElem++)
				{
					pss::TElement elemIn(inElem,i);
					pss::TElement elemOut(outElem, j);
					if (elemIn != elemOut)
					{
						code.setIn(elemIn);
						code.setOut(elemOut);
						generateLinks(code);
					}
				}
			}
		}
	}
}

bool pss::TGenerate::generateLinks(pss::TCode & code)
{
	pss::TReplace linksCombi;		//	������ ��������� ������
	linksCombi.init(pss::TSingletons::getInstance()->getNumberOfLinks());
	do{
		//	��������� ������ ������ � ������ ���������������� ���������
		std::vector<pss::TLink> links;			//	������ ������
		for (int i = 0; i < linksCombi.size(); i++)
			links.push_back(m_allLinks[linksCombi[i]]);
		code.setLinks(links);
		if (code.check())
		{
			if (m_existingSchemes.findIn(code))
			{
				pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_REPETTION, code);
				continue; // RK: BAD style
			}
			m_existingSchemes.add(code);
			generateFrictions(code);
		}
		else
		{
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_0, code);
		}
	} while (linksCombi.nextReplace(m_allLinks.size()-1));
	return true; // RK: fake return true???
}

bool pss::TGenerate::generateFrictions(pss::TCode & code)
{
	//	���������� ��������, �� ������� ����� ���������� ��������
	std::vector<pss::TElement> vect_all_FB = code.getElementsForFrictions();
	if (vect_all_FB.size() == pss::TSingletons::getInstance()->getNumberOfBrakes() + pss::TSingletons::getInstance()->getNumberOfFrictions() + 2)
	{
		std::vector<pss::TLink> vect_all_frict;		//	������ ���� ��������� ����������
		pss::TReplace vect_combi_frict;				//	������ ��������� ����������
		std::vector<pss::TLink> vect_frict;			//	������ ����������
		for (int i = 0; i < vect_all_FB.size(); i++)
			for (int j = i + 1; j < vect_all_FB.size(); j++)
				vect_all_frict.push_back(pss::TLink(vect_all_FB[i], vect_all_FB[j]));
		//	������� ������ ��������� ���������� �� ������ �� Count_F (���������� ����������) ��� ����������: 0,1...
		vect_combi_frict.init(pss::TSingletons::getInstance()->getNumberOfFrictions());
		//	� ����� ���������� ��� ��������� ��������� ����������
		do{
			//	��������� ������ ���������� � ������ ���������������� ���������
			vect_frict.clear();
			for (int i = 0; i < vect_combi_frict.size(); i++)
				vect_frict.push_back(vect_all_frict[vect_combi_frict[i]]);
			code.setFrictions(vect_frict);
			generateBrakes(code);
		} while (vect_combi_frict.nextReplace(vect_all_frict.size() - 1));
	}
	else
	{
		pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_N, code);
	}
	return true;
}

bool pss::TGenerate::generateBrakes(pss::TCode & code)
{
	std::vector<pss::TElement> vect_all_FB = code.getElementsForBrakes();
	pss::TReplace vect_combi_brakes;		//	������ ��������� ��������
	//	������� ������ ��������� �������� �� ���� ��������� �� Count_B
	vect_combi_brakes.init(pss::TSingletons::getInstance()->getNumberOfBrakes());
	do{
		std::vector<pss::TLink> vect_brakes;	//	������ ��������
		//	��������� ������ �������� � ������ ���������������� ���������
		for (int i = 0; i < vect_combi_brakes.size(); i++)
			vect_brakes.push_back(pss::TLink(vect_all_FB[vect_combi_brakes[i]],pss::TElement::BRAKE));
		code.setBrakes(vect_brakes);
		//C.print();
		if (code.checkFree())
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE, code);
		else
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_FREE, code);
	} while (vect_combi_brakes.nextReplace(vect_all_FB.size() - 1));
	return true; // RK: fake true
}
