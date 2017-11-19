#include "DefK.h"

#include "DefKNuton.h"
#include "DefKSimple.h"
#include "DefKSelection.h"
#include "InternalGearRatios.h"

#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"
#include "../Libraries/OrderedSample.h"
#include "../Libraries/GearBoxWithChanger.h"

NS_ARI_USING

void ari::DefK::calcExample()
{
	NS_CORE Log::showValue( "Количество передач:", NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears );

	const float testStep = NS_CORE Singletons::getInstance()->getSettings()->getDefKSettings()._testStep;
	InternalGearRatios K( NS_CORE InternalGearRatioValue( (float)testStep ) );
	const auto &initialData = NS_CORE Singletons::getInstance()->getInitialData();

	NS_CORE Code code;
	int i = 0;
	while ( NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::DONE, code ) )
	{
		i++;
		NS_CORE Log::log( "<", false );
		NS_CORE Log::log( i, false );
		bool isWrited = false;
		NS_CORE GearBoxWithChanger gb( code );

		do
		{
			auto realI = DefKSelection::podModul( gb, K );

			const size_t iSize = realI.size();
			if (iSize >= initialData._numberOfGears)
			{
				int unique = DefKSelection::countOfDifferent(realI, 0.1);

				if ( unique >= initialData._numberOfGears )
				{
					if ( !isWrited )
					{
						NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::K_TEST, code );
						NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, code );
						isWrited = true;
					}
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, realI );
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, K );
				}
			}		
		} while ( K.next() );
		NS_CORE Log::log( ">", false );
	}
}

void DefK::run()
{
	showParams();

	if ( NS_CORE Singletons::getInstance()->getSettings()->getDefKSettings()._doTest )
	{
		calcExample();
		return;
	}

	const auto gears = NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears;
	NS_CORE Code code;
	int i = 0;
	while ( NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::DONE, code ) )
	{
		i++;
		DefKSimple solveSimple;
		NS_CORE Log::log("<", false);
		NS_CORE Log::log(i, false);
		NS_CORE InternalGearRatioArray	 ans = solveSimple.calculate( code );
		
		const auto size = ans.size();
		NS_CORE Log::warning( size > gears, "Error", NS_CORE Log::CRITICAL, HERE );

		if ( !NS_CORE Singletons::getInstance()->getSettings()->getDefKSettings()._calcKQuick && ans.size() == 0 )
		{
			NS_CORE Log::log( "#", false );
			DefKSelection solveSelection;
			ans = solveSelection.calculate( code );
		}

		NS_CORE Log::log(">", false);

		bool isWrited = false;
		const size_t ansSize = ans.size();

		for ( size_t i = 0; i < ansSize; i++ )
		{
			auto realI = DefKSelection::podModul( NS_CORE GearBoxWithChanger( code ), ans[i] );

			if ( ans[i].check() )
			{
				if ( !isWrited )
				{
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, code );
					isWrited = true;
				}
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DONE_K, code );
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DONE_K, ans[i] );
				//NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DONE_K, realI );
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, realI );
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, ans[i] );

			}
		}

	}
	NS_CORE Log::pause();
}

bool ari::DefK::checkRequirements() const
{
	if ( !NS_CORE Singletons::getInstance()->getIOFileManager()->isFileExists( NS_CORE IOFileManager::eOutputFileType::DONE ) )
		return false;

	return true;
}
