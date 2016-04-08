#include <iostream>
#include <fstream>
#include <vector>
#include "../Libraries/func_lib.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TSingletons.h"
#include "DefK.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====\n";
	//Read and calculate
	pss::TSingletons::getInstance()->setGlobalParameters(2, 2);
	pss::TI i({ 5.75, 33.0625 }, 0.1f);
	pss::DefK DK(i);
	const pss::TK K(-6, -1, 1, 6, 0.05);
	pss::TCode code;
	while (pss::TSingletons::getInstance()->getIOFileManager()->loadFromFile(pss::TIOFileManager::eOutputFileType::DONE, code))
	{	
		pss::TK ans(DK.run(code,K));
		if (ans.getFinded())
		{
			//Write to file
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE_K, code);
			pss::TSingletons::getInstance()->getIOFileManager()->writeToFile(pss::TIOFileManager::eOutputFileType::DONE_K, ans);
		}
	}
	system("pause");
	return 0;
}