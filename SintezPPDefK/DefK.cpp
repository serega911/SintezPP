#include "DefK.h"

#include "DefKNuton.h"
#include "DefKSimple.h"
#include "DefKSelection.h"
#include "TK.h"

#include "../Libraries/TSingletons.h"
#include "../Libraries/TLog.h"

NS_ARI_USING


void DefK::readInitialData()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE TLog::log( "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====" );

	readWND();

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

	if ( NS_CORE TSingletons::getInstance()->getInitialData()._w > 2 )
	{
		NS_CORE TLog::log( "Количество передач:	", false );
		int n;
		std::cin >> n;
		NS_CORE TSingletons::getInstance()->setNumberOfGears( n );
	}
	else
	{
		NS_CORE TSingletons::getInstance()->setNumberOfGears( NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
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

void ari::DefK::calcExample()
{
	readWND();
	if ( NS_CORE TSingletons::getInstance()->getInitialData()._w > 2 )
	{
		NS_CORE TLog::log( "Количество передач:	", false );
		int n;
		std::cin >> n;
		NS_CORE TSingletons::getInstance()->setNumberOfGears( n );
	}
	else
	{
		NS_CORE TSingletons::getInstance()->setNumberOfGears( NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	}

	const auto &initialData = NS_CORE TSingletons::getInstance()->getInitialData();
	
	NS_CORE TKValueArray kValues;
	for ( size_t i = 0; i < initialData._numberOfPlanetaryGears; i++ )
		kValues.push_back( NS_CORE TKValue( 2 ) );
	ari::TK k = NS_CORE TK( kValues );

	NS_CORE TCode code;
	while ( NS_CORE TSingletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE TIOFileManager::eOutputFileType::DONE, code ) )
	{
		auto realI = DefKSelection::podModul( code, k );

		if (realI.size() > 0 )
		{
			int unique = 1;
			for ( int i = 0; i < realI.size() - 1; i++ )
			{
				bool finded = false;
				for ( int j = i + 1; j < realI.size(); j++ )
				{
					if ( realI[i] == realI[j] )
					{
						finded = true;
						break;
					}
				}

				if ( !finded )
				{
					unique++;
				}

			}
			if ( unique == initialData._numberOfGears )
			{
				NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::K_TEST, code );
			}
		}	
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

		if ( !NS_CORE TSingletons::getInstance()->getSettings()->getDefKSettings()._calcKQuick && ans.size() == 0)
		{
			NS_CORE TLog::log( "#", false );
			DefKSelection solveSelection;
			ans = solveSelection.calculate( code );
		}
		

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