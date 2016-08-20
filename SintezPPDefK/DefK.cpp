#include "DefK.h"

#include "DefKNuton.h"
#include "DefKSimple.h"
#include "DefKSelection.h"

#include "../Libraries/TSingletons.h"
#include "../Libraries/TLog.h"

NS_ARI_USING


void DefK::readInitialData()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE TLog::log( "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====" );

	int W;
	int N;
	NS_CORE TLog::log( "\t\t\tИсходные данные." );
	NS_CORE TLog::log( "Число степеней свободы:	", false );
	std::cin >> W;
	NS_CORE TLog::log( "Количество ПМ:		", false );
	std::cin >> N;
	NS_CORE TSingletons::getInstance()->setGlobalParameters( W, N );

	int countIntervals = 0;
	NS_CORE TLog::log( "Количество диапазонов : ", false );
	std::cin >> countIntervals;
	for ( int i = 0; i < countIntervals; i++ )
	{
		double beg, end;
		NS_CORE TLog::log( "Начало диапазона:	", false );
		std::cin >> beg;
		NS_CORE TLog::log( "Конец диапазона:	", false );
		std::cin >> end;
		NS_CORE TSingletons::getInstance()->addRangeK( NS_CORE TRange( beg, end ) );
	}
	NS_CORE TLog::log( "Передаточные отношения:	", false );
	for ( int i = 0; i < NS_CORE TSingletons::getInstance()->getInitialData()._numberOfGears; i++ )
	{
		double ratio = 0;
		std::cin >> ratio;
		if ( ratio != 0 )
			NS_CORE TSingletons::getInstance()->addGearRatio( ratio );
		else
			break;
	}
}

void DefK::run()
{ 
	readInitialData();

	NS_CORE TCode code;

	while ( NS_CORE TSingletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE TIOFileManager::eOutputFileType::DONE, code ) )
	{
		
		DefKSimple solveSimple;
		NS_CORE TK ansSimple( solveSimple.calculate( code ) );

		DefKNuton solveNuton;
		NS_CORE TK ansNuton( solveNuton.calculate( code ) );

		DefKSelection solveSelection;
		NS_CORE TK ansSelection( solveSelection.calculate( code ) );

		if ( ansSimple.check() || ansNuton.check() || ansSelection.check() )
		{
			NS_CORE TK ans;
			if ( ansSimple.check() )
				ans = ansSimple;
			else if ( ansNuton.check() )
				ans = ansNuton;
			else if ( ansSelection.check() )
				ans = ansSelection;

			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, code );
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, ans );
		}

	}
}