#include "TGenerate.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TReplace.h"
#include <iostream>

#include <algorithm>

void pss::TGenerate::generate()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "======  Синтез планетарных передач с тремя степенями свободы.  ======\n\n";
	//	Исходные данные
	int W;
	int N;
	std::cout << "\t\t\tИсходные данные." << std::endl << "Число степеней свободы:	";
	std::cin >> W;
	std::cout << "Количество ПМ:		";
	std::cin >> N;
	pss::TSingletons::getInstance()->setGlobalParameters(W, N);
	std::cout << "Количество связей:	" << pss::TSingletons::getInstance()->getNumberOfLinks() << std::endl;
	std::cout << "Количество фрикционов:	" << pss::TSingletons::getInstance()->getNumberOfFrictions() << std::endl;
	std::cout << "Количество тормозов:	" << pss::TSingletons::getInstance()->getNumberOfBrakes() << std::endl;

	//	Заполняем вектор всех возможных связей, пропускаем связи между элементами одного ряда.
	m_allLinks.clear();
	for (int i = 0; i <= 3 * (N - 1); i++)
	{
		for (int j = (i / 3 + 1) * 3; j < 3 * N; j++)
			m_allLinks.push_back(pss::pos_2_code(i) * 100 + pss::pos_2_code(j));
	}
	generateInOut();
}

void pss::TGenerate::generateInOut()
{
	pss::TCode code;
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	for (int in = 0; in < 3 * N; in++)				//	Вход на все звенья
		for (int out = 0; out < 3 * N; out++)		//	Выход на все звенья
		{
			if (in != out)							//	Проверка: вход и выход не могут быть одним и тем же элементом
			{
				code.clear();
				code.setIn(pss::pos_2_code(in));
				code.setOut(pss::pos_2_code(out));
				generateLinks(code);
			}
		}
}

bool pss::TGenerate::generateLinks(pss::TCode & code)
{
	pss::TReplace linksCombi;		//	Вектор сочетаний связей
	linksCombi.init(pss::TSingletons::getInstance()->getNumberOfLinks());
	do{
		//	Заполняем вектор связей с учетом сгенерированного сочетания
		std::vector<int> links;			//	Вектор связей
		for (int i = 0; i < linksCombi.size(); i++)
			links.push_back(m_allLinks[linksCombi[i]]);
		code.setLinks(links);
		if (m_existingSchemes.findIn(code))
		{
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_REPETTION, code);
			continue;
		}	
		m_existingSchemes.add(code);
		if (code.check())
		{
			generateFrictions(code);
		}
		else
		{
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_0, code);
		}
	} while (linksCombi.nextReplace(m_allLinks.size()-1));
	return true;
}

bool pss::TGenerate::generateFrictions(pss::TCode & code)
{
	//	Определяем элементы, на которых будет установлен фрикцион или тормоз
	std::vector<int> vect_all_FB = code.getOneElemFromOneChain();
	vect_all_FB.push_back(code.getIn());
	vect_all_FB.push_back(code.getOut());
	if (vect_all_FB.size() == pss::TSingletons::getInstance()->getNumberOfBrakes() + pss::TSingletons::getInstance()->getNumberOfFrictions()+2)
	{
		std::vector<int> vect_all_frict;		//	Вектор всех возможных фрикционов
		pss::TReplace vect_combi_frict;		//	Вектор сочетаний фрикционов
		std::vector<int> vect_frict;			//	Вектор фрикционов
		for (int i = 0; i < vect_all_FB.size(); i++)
			for (int j = i + 1; j < vect_all_FB.size(); j++)
				vect_all_frict.push_back(vect_all_FB[i] * 100 + vect_all_FB[j]);
		//	Создаем первое сочетание фрикционов из связей по Count_F (количество фрикционов) без повторений: 0,1...
		vect_combi_frict.init(pss::TSingletons::getInstance()->getNumberOfFrictions());
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
	return true;
}

bool pss::TGenerate::generateBrakes(pss::TCode & code)
{
	std::vector<int> vect_all_FB = code.getOneElemFromOneChain();
	pss::TReplace vect_combi_brakes;		//	Вектор сочетаний тормозов
	//	Создаем первое сочетание тормозов из всех возможных по Count_B
	vect_combi_brakes.init(pss::TSingletons::getInstance()->getNumberOfBrakes());
	do{
		std::vector<int> vect_brakes;	//	Вектор тормозов
		//	Заполняем вектор тормозов с учетом сгенерированного сочетания
		for (int i = 0; i < vect_combi_brakes.size(); i++)
			vect_brakes.push_back(vect_all_FB[vect_combi_brakes[i]]);
		code.setBrakes(vect_brakes);
		//C.print();
		if (code.checkFree())
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE, code);
		else
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::FAIL_FREE, code);
	} while (vect_combi_brakes.nextReplace(vect_all_FB.size() - 1));
	return true;
}
