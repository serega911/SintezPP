#include "DefK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>

pss::DefK::DefK()
{
}


pss::DefK::~DefK(void)
{
}

pss::TK pss::DefK::findK(const pss::TCode& Code, pss::TK K)
{
	do{
		//K.print();
		if (podModul(Code, K))
		{
			K.setFinded();
			return K;
		}
		//system("pause");
	}while(K.next());
	return K;
}

void pss::DefK::run()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====\n";
	//	Исходные данные
	int W;
	int N;
	std::cout << "\t\t\tИсходные данные." << std::endl << "Число степеней свободы:	";
	std::cin >> W;
	std::cout << "Количество ПМ:		";
	std::cin >> N;
	pss::TSingletons::getInstance()->setGlobalParameters(W, N);
	double dK = 0;
	std::cout << "Шаг поиска К:		";
	std::cin >> dK;
	pss::TK K(dK);
	int countIntervals = 0;
	std::cout << "Количество диапазонов:	";
	std::cin >> countIntervals;
	for (int i = 0; i < countIntervals; i++)
	{
		double beg, end;
		std::cout << "Начало диапазона:	";
		std::cin >> beg;
		std::cout << "Конец диапазона:	";
		std::cin >> end;
		K.addInterval(beg, end);
	}
	std::cout << "Передаточные отношения:	";
	for (int i = 0; i < pss::TSingletons::getInstance()->getNumberOfGears(); i++)
	{
		double ratio = 0;
		std::cin >> ratio;
		if (ratio != 0)
			m_iTarget.push_back(ratio);
		else
			break;
	}
	pss::TCode code;
	while (pss::TSingletons::getInstance()->getIOFileManager()->loadFromFile(pss::TIOFileManager::eOutputFileType::DONE, code))
	{
		pss::TK ans(findK(code, K));
		if (ans.getFinded())
		{
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE_K, code);
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE_K, ans);
		}
	}
}

bool pss::DefK::podModul(const pss::TCode & Code, const pss::TK &k)
{
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	auto L = pss::TSingletons::getInstance()->getNumberOfLinks();
	auto F = pss::TSingletons::getInstance()->getNumberOfFrictions();
	auto B = pss::TSingletons::getInstance()->getNumberOfBrakes();
	auto W = pss::TSingletons::getInstance()->getW();

	m_matrix.resize(3 * N);
	for (auto& it : m_matrix)
		it.resize(3 * N + 1);
	//в первые N строк записываем уравнения Виллиса. 
	//Эти строки никогда не очищаем так как все значения всегда пишутся на одни и те же позиции
	for (int i = 0; i < k.size(); i++){
		m_matrix[i][3 * i] = 1;
		m_matrix[i][3 * i + 1] = -k[i];
		m_matrix[i][3 * i + 2] = k[i] - 1;
	}

		//system("pause");
		//очищаем уравнения
	for (int i = N; i < N + L + 1; i++)
		for (int j = 0; j < 3 * N + 1; j++)
				m_matrix[i][j] = 0;
	//в следующие countSV строк записываем связи
	for (int i = N, j = 2; i < N + L; i++, j++)
	{
		m_matrix[i][Code[j].getElem1().getSerialNumber()] = 1;
		m_matrix[i][Code[j].getElem2().getSerialNumber()] = -1;
	}
	//уравнение для звена, связанного с ведущим валом

	m_matrix[N + L][Code[0].getElem1().getSerialNumber()] = 1;
	m_matrix[N + L][N * 3] = 1;
			
	//print(Matrix, "11	21	31	12	22	32	13	23	33	RP \n___________________________________________________________________________");
	
	pss::TI tmpI({}, 0.01);	//вектор для полученных передаточных отношений при данном наборе K
	double TMP=0;

	std::vector<int> vect_combi_drive(W - 1);//TReplace
	for (int i = 0; i < W - 1; i++)
	vect_combi_drive[i] = i;
	//перебераем все сочетания включения элементов управления (фрикционов и тормозов) без повторений
	do {
		//записываем в матрицу уравнения с элементами управления
		for (int i = 0; i < vect_combi_drive.size(); i++)
		{
			pss::TLink driver = Code[2 + L + vect_combi_drive[i]];
			//std::cout << "driver: " << driver << std::endl;
			if (driver.getElem2() == pss::TElement::BRAKE)	//driver - тормоз
				m_matrix[N + L + 1 + i][driver.getElem1().getSerialNumber()] = 1;
			else	//driver - фрикцион
			{
				m_matrix[N + L + 1 + i][driver.getElem1().getSerialNumber()] = 1;
				m_matrix[N + L + 1 + i][driver.getElem2().getSerialNumber()] = -1;
			}
		}
		//print(Matrix, "11	21	31	12	22	32	13	23	33	RP\n___________________________________________________________________________");
		//решаем систему уравнений
		TMP = pss::GAUS(m_matrix, Code[1].getElem1().getSerialNumber());
		//проверяем результат
		if (abs(TMP) > 0.001)
			tmpI.push_back(1.0 / TMP);
		else
			return false;
		//очищаем уравнения с элементами управления
		for (int i = N + L + 1; i < N + L + W; i++)
			for (int j = 0; j < 3 * N + 1; j++)
				m_matrix[i][j] = 0;
	} while (pss::next_combination(vect_combi_drive, F + B - 1));
			//сравниваем полученные передаточные отношения с искомыми
	if (m_iTarget == tmpI)
	{
		m_iReal = tmpI;
		return true;
	}
	else
		return false;
}

