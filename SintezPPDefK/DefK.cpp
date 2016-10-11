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

	size_t w;
	size_t n;
	size_t d;
	NS_CORE TLog::log( "\t\t\tИсходные данные." );
	NS_CORE TLog::log( "Число степеней свободы:	", false );
	std::cin >> w;
	NS_CORE TLog::log( "Количество ПМ:		", false );
	std::cin >> n;
	NS_CORE TLog::log( "Количество элементов управления:	", false );
	std::cin >> d;
	NS_CORE TSingletons::getInstance()->setGlobalParameters( w, n, d );

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
		NS_CORE TSingletons::getInstance()->addRangeK( NS_CORE TRange( NS_CORE TKValue( beg ), NS_CORE TKValue( end ) ) );
	}

	if ( w > 2 )
	{
		NS_CORE TLog::log( "Максимально допустимое количество передач - ", false );
		NS_CORE TLog::log( NS_CORE TSingletons::getInstance()->getInitialData()._numberOfGears );
		NS_CORE TLog::log( "Количество передач:	", false );
		int n1;
		std::cin >> n1;
		NS_CORE TSingletons::getInstance()->setNumberOfGears( n1 );
	}
	else
	{
		NS_CORE TSingletons::getInstance()->setNumberOfGears( n );
	}

	NS_CORE TLog::log( "Передаточные отношения : ", false );
	for ( size_t i = 0; i < NS_CORE TSingletons::getInstance()->getInitialData()._numberOfGears; i++ )
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
		NS_CORE TKArray	 ans = solveSimple.calculate( code );
		NS_CORE TLog::log( ".", false );
#define  QUICK_SEARCH
#ifndef QUICK_SEARCH 
		if ( !solveSimple.getIsCanFind() )
		{
			NS_CORE TLog::log( "#", false );
			DefKSelection solveSelection;
			ans = solveSelection.calculate( code );
		}
#endif

		bool isWrited = false;
		

		for ( size_t i = 0; i < ans.size(); i++ )
		{
			auto realI = DefKSelection::podModul( code, ans[i] );

			if ( ans[i].check() )
			{
				if ( !isWrited )
				{
					NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, code );
					isWrited = true;
				}
				NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, realI );
				NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, ans[i] );	
			}
		}
		
	}	
	system( "pause" );
}