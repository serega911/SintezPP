#include "DefK.h"
#include "DefKNuton.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TGaus.h"
#include "../Libraries/TGearChanger.h"


#include <iostream>

NS_PSS_USING

TK DefK::findK( const TCode& Code )
{

	std::vector<double> initialK;
	std::vector<int> combi;

	for ( auto i = 0; i < TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears; i++ )
	{
		combi.push_back( 0 );
	}
	initialK.resize( TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
		
	TK ans;

	do{
		for ( auto i = 0; i < initialK.size(); i++ )
			initialK[i] = TSingletons::getInstance()->getInitialData()._ranges[combi[i]].getMid();

		TK initial;
		initial.setValues( initialK );
		initial.print();

		NS_PSS DefKNuton defKByNonlinearSolving;
		ans = defKByNonlinearSolving.findK( Code, initial );

		if ( ans.getFinded() )
		{
			break;
		}
		//system( "pause" );
	} while ( next_combination_repetition( combi, TSingletons::getInstance()->getInitialData()._ranges.size() - 1, 0 ) );

	return ans;
}

void DefK::run()
{
	
	readInitialData();

	TCode code;
	while (TSingletons::getInstance()->getIOFileManager()->loadFromFile(TIOFileManager::eOutputFileType::DONE, code))
	{
		code.createChains();
		TK ans( findK(code) );
		if (ans.getFinded())
		{
			TSingletons::getInstance()->getIOFileManager()->writeToFile(TIOFileManager::eOutputFileType::DONE_K, code);
			TSingletons::getInstance()->getIOFileManager()->writeToFile(TIOFileManager::eOutputFileType::DONE_K, ans);
		}
	}
}

void pss::DefK::readInitialData()
{
	setlocale( LC_ALL, "Russian" );
	std::cout << "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====\n";
	
	//	Исходные данные
	int W;
	int N;
	std::cout << "\t\t\tИсходные данные." << std::endl << "Число степеней свободы:	";
	std::cin >> W;
	std::cout << "Количество ПМ:		";
	std::cin >> N;
	TSingletons::getInstance()->setGlobalParameters( W, N );

	int countIntervals = 0;
	std::cout << "Количество диапазонов:	";
	std::cin >> countIntervals;
	for ( int i = 0; i < countIntervals; i++ )
	{
		double beg, end;
		std::cout << "Начало диапазона:	";
		std::cin >> beg;
		std::cout << "Конец диапазона:	";
		std::cin >> end;
		TSingletons::getInstance()->addRangeK( TRange( beg, end ) );
	}
	std::cout << "Передаточные отношения:	";
	for ( int i = 0; i < TSingletons::getInstance()->getInitialData()._numberOfGears; i++ )
	{
		double ratio = 0;
		std::cin >> ratio;
		if ( ratio != 0 )
			TSingletons::getInstance()->addGearRatio( ratio );
		else
			break;
	}
}

