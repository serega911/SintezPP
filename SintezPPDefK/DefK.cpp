#include "DefK.h"
#include "DefKNuton.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TGaus.h"
#include "../Libraries/TCombinations.h"
#include "../Libraries/TGearChanger.h"
#include "../Libraries/TLog.h"

#include <algorithm>
#include <iostream>

NS_PSS_USING

TK DefK::findK( const TCode& Code )
{
	TK ans;

	checkAllInitialKValues( Code, ans );

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
			//TLog::log( "+", false );
		}
		//TLog::log( "" );
	}
}

void pss::DefK::readInitialData()
{
	setlocale( LC_ALL, "Russian" );

	TLog::log( "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====" );
	
	//	Исходные данные
	int W;
	int N;
	TLog::log( "\t\t\tИсходные данные." );
	TLog::log( "Число степеней свободы:	", false );
	std::cin >> W;
	TLog::log( "Количество ПМ:		", false );
	std::cin >> N;
	TSingletons::getInstance()->setGlobalParameters( W, N );

	int countIntervals = 0;
	TLog::log( "Количество диапазонов : ", false );
	std::cin >> countIntervals;
	for ( int i = 0; i < countIntervals; i++ )
	{
		double beg, end;
		TLog::log( "Начало диапазона:	", false );
		std::cin >> beg;
		TLog::log( "Конец диапазона:	", false );
		std::cin >> end;
		TSingletons::getInstance()->addRangeK( TRange( beg, end ) );
	}
	TLog::log( "Передаточные отношения:	", false );
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

void pss::DefK::checkAllInitialKValues( const TCode& Code, TK& ret )
{

	std::vector<int> combi;
	for ( auto i = 0; i < TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears; i++ )
		combi.push_back( 0 );

	do{

		std::vector<double> initialK;
		for ( auto i = 0; i < combi.size(); i++ )
			initialK.push_back(TSingletons::getInstance()->getInitialData()._ranges[combi[i]].getMid());

		TK initial;
		initial.setValues( initialK );

		checkAllRatiosPermutations( Code, initial, ret );

	} while ( !ret.getFinded() && next_combination_repetition( combi, TSingletons::getInstance()->getInitialData()._ranges.size() - 1, 0 ) );
}

void pss::DefK::checkAllRatiosPermutations( const TCode& Code, const TK& initial, TK& ret )
{
	TI iTarget = TSingletons::getInstance()->getInitialData()._i;

	std::vector<int> replace;
	for ( int i = 0; i < iTarget.size(); i++ )
		replace.push_back( i );

	do{

		std::vector<double> curI;
		for ( int i = 0; i < iTarget.size(); i++ )
			curI.push_back( iTarget[replace[i]] );

		NS_PSS DefKNuton defKByNonlinearSolving;
		ret = defKByNonlinearSolving.findK( Code, initial, TI( curI, 0.1 ) );

	} while ( !ret.getFinded() && std::next_permutation( replace.begin(), replace.end() ) );
}

