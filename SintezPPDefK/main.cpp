#include <iostream>
#include <fstream>
#include <vector>
#include "../Libraries/func_lib.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TSingletons.h"
#include "DefK.h"
//#include "DefK_intel.h"

int main(float eps, float dk, float beginNegative, float endNegative, float beginPositive, float endPositive)
{
	// Debug init
	beginNegative = -6.0f;
	endNegative = -2.0f;
	beginPositive = -2.0f;
	endPositive = -2.0f;
	dk = 0.05f;
	eps = 0.1;

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

	//Read and calculate
	pss::TI i({ 5.75, 33.0625 }, 0.05f);
	pss::TCode code;
	pss::TK K(beginNegative, endNegative, beginPositive, endPositive, dk);
	pss::DefK DK(i);

	int c = 1;

	while (pss::TSingletons::getInstance()->getIOFileManager()->loadFromFile(pss::TIOFileManager::eOutputFileType::DONE, code)){		
		pss::TK ans = DK.Run(code,K);
		if (ans.getFinded())
		{
			std::cout << "DONE!!!!!!\n";
			//Write to file
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE_K, code);
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE_K, ans);
			
		}
		std::cout << c++ << ' ';
	}
	system("pause");

	return 0;
}