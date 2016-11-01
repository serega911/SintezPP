#include "DefK.h"

#include "DefKNuton.h"
#include "DefKSimple.h"
#include "DefKSelection.h"
#include "InternalGearRatios.h"

#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"

NS_ARI_USING


void DefK::readInitialData()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE Log::log( "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====" );

	readWND();

	int countIntervals = 0;
	NS_CORE Log::log( "Количество диапазонов : ", false );
	std::cin >> countIntervals;
	for ( int i = 0; i < countIntervals; i++ )
	{
		double beg, end;
		NS_CORE Log::log( "Начало диапазона:	", false );
		std::cin >> beg;
		NS_CORE Log::log( "Конец диапазона:	", false );
		std::cin >> end;
		NS_CORE Singletons::getInstance()->addRangeK( NS_CORE Range( NS_CORE InternalGearRatioValue( beg ), NS_CORE InternalGearRatioValue( end ) ) );
	}

	if ( NS_CORE Singletons::getInstance()->getInitialData()._w > 2 )
	{
		NS_CORE Log::log( "Количество передач:	", false );
		int n;
		std::cin >> n;
		NS_CORE Singletons::getInstance()->setNumberOfGears( n );
	}
	else
	{
		NS_CORE Singletons::getInstance()->setNumberOfGears( NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	}

	NS_CORE Log::log( "Передаточные отношения : ", false );
	for ( size_t i = 0; i < NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears; i++ )
	{
		double ratio = 0;
		std::cin >> ratio;
		if ( ratio != 0 )
			NS_CORE Singletons::getInstance()->addGearRatio( ratio );
		else
			break;
	}
}

void ari::DefK::calcExample()
{
	readWND();
	if ( NS_CORE Singletons::getInstance()->getInitialData()._w > 2 )
	{
		NS_CORE Log::log( "Количество передач:	", false );
		int n;
		std::cin >> n;
		NS_CORE Singletons::getInstance()->setNumberOfGears( n );
	}
	else
	{
		NS_CORE Singletons::getInstance()->setNumberOfGears( NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	}

	const auto &initialData = NS_CORE Singletons::getInstance()->getInitialData();
	
	NS_CORE InternalGearRatioValueArray kValues[3];
	for ( size_t i = 0; i < initialData._numberOfPlanetaryGears; i++ )
	{
		kValues[0].push_back( NS_CORE InternalGearRatioValue( 2 ) );
		kValues[1].push_back( NS_CORE InternalGearRatioValue( 3 ) );
		kValues[2].push_back( NS_CORE InternalGearRatioValue( -2 ) );
	}
	ari::InternalGearRatios initialK[] =	{ 
										NS_CORE InternalGearRatios( kValues[0] ),
										NS_CORE InternalGearRatios( kValues[1] ),
										NS_CORE InternalGearRatios( kValues[2] )
									};


	NS_CORE Code code;
	while ( NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::DONE, code ) )
	{
		for ( const auto &k : initialK )
		{
			auto realI = DefKSelection::podModul( code, k );

			if ( realI.size() > 0 )
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
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::K_TEST, code );
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::K_TEST_LOG, code );
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::K_TEST_LOG, realI );
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::K_TEST_LOG, k );
				}
			}
		}	
	}
}

void DefK::run()
{ 
	readInitialData();

	NS_CORE Code code;

	while ( NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::DONE, code ) )
	{
		DefKSimple solveSimple;
		NS_CORE InternalGearRatioArray	 ans = solveSimple.calculate( code );
		NS_CORE Log::log( ".", false );

		if ( !NS_CORE Singletons::getInstance()->getSettings()->getDefKSettings()._calcKQuick && ans.size() == 0)
		{
			NS_CORE Log::log( "#", false );
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
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DONE_K, code );
					isWrited = true;
				}
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DONE_K, realI );
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DONE_K, ans[i] );	
			}
		}
		
	}	
	system( "pause" );
}