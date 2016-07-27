#include "TGenerate.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TCombinations.h"
#include "../Libraries/TLog.h"
#include <iostream>


void pss::TGenerate::generate()
{
	setlocale(LC_ALL, "Russian");
	TLog::log( "====  Синтез планетарных передач с тремя степенями свободы. Генерация.  ====\n\n" );
	//	Исходные данные
	int W = 0;
	int N = 0;
	TLog::log( "\t\t\tИсходные данные." );
	TLog::log( "Число степеней свободы:	", false );
	std::cin >> W;
	TLog::log( "Количество ПМ:		", false );
	std::cin >> N;
	pss::TSingletons::getInstance()->setGlobalParameters(W, N);

	auto generalData = pss::TSingletons::getInstance()->getGeneralData();
	TLog::log( "Количество связей:	" + std::to_string( generalData._numberOfLinks ) );
	TLog::log( "Количество фрикционов:	" + std::to_string( generalData._numberOfFrictions ) );
	TLog::log( "Количество тормозов:	" + std::to_string( generalData._numberOfBrakes ) );

	//	Заполняем вектор всех возможных связей, пропускаем связи между элементами одного ряда и реверсивные связи.
	m_allLinks.clear();
	for (int i = 1; i < N; i++)
	{
		for ( const auto& mElem1 : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
		{
			for (int j = i + 1; j <= N; j++)
			{
				for ( const auto& mElem2 : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
				{
					m_allLinks.push_back( pss::TLink( pss::TElement( mElem1, i ), pss::TElement( mElem2, j ) ) );
				}
			}
		}
	}

	generateInOut();
}

void pss::TGenerate::generateInOut()
{
	pss::TCode code;
	auto N = pss::TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	for (int i = 1; i <= N; i++)
	{
		for ( const auto& inElem : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
		{
			for (int j = 1; j <= N; j++)
			{
				for ( const auto& outElem : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
				{
					pss::TElement elemIn( inElem, i );
					pss::TElement elemOut(  outElem, j );
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

void pss::TGenerate::generateLinks(pss::TCode & code)
{
	pss::TCombinations linksCombi;		//	Вектор сочетаний связей
	linksCombi.init( pss::TSingletons::getInstance()->getGeneralData()._numberOfLinks );
	do{
		//	Заполняем вектор связей с учетом сгенерированного сочетания
		std::vector<pss::TLink> links;			//	Вектор связей
		for (int i = 0; i < linksCombi.size(); i++)
			links.push_back(m_allLinks[linksCombi[i]]);
		code.setLinks(links);
		if (code.check())
		{
			if (m_existingSchemes.findIn(code))
			{
				pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_REPETTION, code);
			}
			else
			{
				m_existingSchemes.add(code);
				generateFrictions(code);
			}
		}
		else
		{
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_0, code);
		}
	} while (linksCombi.nextReplace(m_allLinks.size()-1));
}

void pss::TGenerate::generateFrictions(pss::TCode & code)
{
	//	Определяем элементы, на которых будет установлен фрикцион
	std::vector<pss::TElement> vect_all_FB = code.getElementsForFrictions();

	const auto& generalData = pss::TSingletons::getInstance()->getGeneralData();

	if ( vect_all_FB.size() == generalData._numberOfBrakes + generalData._numberOfFrictions + 2 )
	{
		std::vector<pss::TLink> vect_all_frict;		//	Вектор всех возможных фрикционов
		pss::TCombinations vect_combi_frict;				//	Вектор сочетаний фрикционов
		std::vector<pss::TLink> vect_frict;			//	Вектор фрикционов
		for (int i = 0; i < vect_all_FB.size(); i++)
			for (int j = i + 1; j < vect_all_FB.size(); j++)
				vect_all_frict.push_back(pss::TLink(vect_all_FB[i], vect_all_FB[j]));
		//	Создаем первое сочетание фрикционов из связей по Count_F (количество фрикционов) без повторений: 0,1...
		vect_combi_frict.init( generalData._numberOfFrictions );
		//	В цикле генерируем все возможные сочетания фрикционов
		do{
			//	Заполняем вектор фрикционов с учетом сгенерированного сочетания
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
}

void pss::TGenerate::generateBrakes(pss::TCode & code)
{
	std::vector<pss::TElement> vect_all_FB = code.getElementsForBrakes();
	pss::TCombinations vect_combi_brakes;		//	Вектор сочетаний тормозов
	//	Создаем первое сочетание тормозов из всех возможных по Count_B
	vect_combi_brakes.init( pss::TSingletons::getInstance()->getGeneralData()._numberOfBrakes );
	do{
		std::vector<pss::TLink> vect_brakes;	//	Вектор тормозов
		//	Заполняем вектор тормозов с учетом сгенерированного сочетания
		for (int i = 0; i < vect_combi_brakes.size(); i++)
			vect_brakes.push_back(pss::TLink(vect_all_FB[vect_combi_brakes[i]],pss::TElement::BRAKE));
		code.setBrakes(vect_brakes);
		//C.print();
		if (code.checkFree())
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE, code);
		else
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_FREE, code);
	} while (vect_combi_brakes.nextReplace(vect_all_FB.size() - 1));
}
