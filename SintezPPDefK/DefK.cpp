#include "DefK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TGaus.h"
#include "../Libraries/TGearChanger.h"
#include <iostream>

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
			break;
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

bool pss::DefK::podModul(const pss::TCode & code, const pss::TK &k)
{
	pss::TGearChanger gearChanger(code);
	pss::TI tmpI({}, 0.01);	//вектор для полученных передаточных отношений при данном наборе K
	do
	{
		pss::TGaus gaus;
		gaus.createSystem(code, k);
		gaus.createSystemDrivers(gearChanger.getDrivingElementsForGear());
		gaus.solve();
		if ( gaus.getSolution().size() == 0 )
		{
			return false;
		}
		float calculatedI = gaus.getSolution()[code[1].getElem1().getSerialNumber()];
		if ( abs( calculatedI ) > 0.001 && m_iTarget.findIn( 1.0 / calculatedI ) )
		{
			tmpI.push_back( 1.0 / calculatedI );
		}
		else
		{
			return false;
		}
			
	} while (gearChanger.next());
	//сравниваем полученные передаточные отношения с искомыми
	if (m_iTarget == tmpI)
	{
		m_iReal = tmpI;
		return true;
	}
	else
		return false;
}

