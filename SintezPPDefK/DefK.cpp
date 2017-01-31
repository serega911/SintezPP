#include "DefK.h"

#include "DefKNuton.h"
#include "DefKSimple.h"
#include "DefKSelection.h"
#include "InternalGearRatios.h"

#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"
#include "../Libraries/Log.h"

NS_ARI_USING




void ari::DefK::calcExample()
{

	NS_CORE Log::showValue( "Количество передач:", NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears );

	const auto &initialData = NS_CORE Singletons::getInstance()->getInitialData();
	
	const size_t testKSize = NS_CORE Singletons::getInstance()->getSettings()->getDefKSettings()._testsCount;
	std::vector<NS_CORE InternalGearRatioValueArray> kValues(testKSize);
	for ( size_t i = 0; i < initialData._numberOfPlanetaryGears; i++ )
	{
		for ( int j = 0; j < testKSize; j++ )
			kValues[j].emplace_back( NS_CORE InternalGearRatioValue( ( rand() % 30 ) / 10.0 + 2 ) );
	}

	std::vector<ari::InternalGearRatios> initialK;
	for ( int j = 0; j < testKSize; j++ )
		initialK.emplace_back( NS_CORE InternalGearRatios( kValues[j] ) );

	NS_CORE Code code;
	while ( NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::DONE, code ) )
	{
		bool isWrited = false;

		for ( const auto &k : initialK )
		{
			auto realI = DefKSelection::podModul( code, k );

			const size_t iSize = realI.size();
			if ( iSize > 0 )
			{
				int unique = 1;
				for ( int i = 0; i < iSize - 1; i++ )
				{
					if ( realI[i] != NS_CORE RatioValue( 0 ) )
					{
						bool finded = false;
						for ( int j = i + 1; j < iSize; j++ )
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
				}
				if ( unique == initialData._numberOfGears )
				{
					if (!isWrited)
					{
						NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile(NS_CORE IOFileManager::eOutputFileType::K_TEST, code);
						NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile(NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, code);
						isWrited = true;
					}
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, realI );
					NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DEF_K_LOG, k );
				}
			}
		}	
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
		const size_t ansSize = ans.size();

		for ( size_t i = 0; i < ansSize; i++ )
		{
			auto realI = DefKSelection::podModul( code, ans[i] );

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
	system( "pause" );
}

bool ari::DefK::checkRequirements() const
{
	if ( !NS_CORE Singletons::getInstance()->getIOFileManager()->isFileExists( NS_CORE IOFileManager::eOutputFileType::DONE ) )
		return false;

	return true;
}
