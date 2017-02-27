#include <iostream>

#include "../Libraries/SchemeCharacteristics.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/CombinatoricsValueArray.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/IIOItem.h"

#include "KinematicSchemeBuilder.h"
#include "SchemeBuilderSwapPrev.h"
#include "SchemeBuilderMoveFirst.h"
#include "GearSetFactory.h"
#include "PathBuilderLee.h"
#include "Scheme.h"



NS_ARI_USING

void KinematicSchemeBuilder::run()
{
	core::Code code;
	core::InternalGearRatios k;
	std::vector<core::IIOItem*> containers;
	containers.push_back( &code );
	containers.push_back( &k );
	auto& facory = GearSetFactory::getInstance();

	while ( core::Singletons::getInstance()->getLoaderFromFile()->load( containers, core::IOFileManager::eOutputFileType::DONE_K ) )
	{
		facory->init(k);
		do 
		{
			IScheme_p scheme = Scheme::create();
			ITraceStrategy_p pathBuilder = PathBuilderLee::create();
			ISchemeBuildStartegy_p schemeBuilderSwap = SchemeBuilderSwapPrev::create();
			ISchemeBuildStartegy_p schemeBuilderMove = SchemeBuilderMoveFirst::create();

			if ( schemeBuilderMove->run( scheme, pathBuilder, code ) || schemeBuilderSwap->run( scheme, pathBuilder, code ) )
			{
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW, code );
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW, k );
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW, facory->getTypes() );
				break;
			}
		} while ( facory->next() );
	}
}

bool ari::KinematicSchemeBuilder::checkRequirements() const
{
	if ( !NS_CORE Singletons::getInstance()->getIOFileManager()->isFileExists( NS_CORE IOFileManager::eOutputFileType::DONE_K ) )
		return false;

	NS_CORE Ratios i;
	NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::INITIAL_DATA, i );

	if ( i.size() != NS_CORE Singletons::getInstance()->getInitialData()._i.size() )
		return false;

	NS_CORE Range range( NS_CORE InternalGearRatioValue( 0 ), NS_CORE InternalGearRatioValue( 0 ) );
	const auto& ranges = NS_CORE Singletons::getInstance()->getInitialData()._ranges;

	int count = 0;

	while ( NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::INITIAL_DATA, range ) )
	{
		bool finded = false;
		count++;
		for ( const auto& r : ranges )
		{
			if ( r == range )
			{
				finded = true;
				break;
			}
		}

		if ( !finded )
			return false;

	}

	if ( count != ranges.size() )
		return false;

	return true;
}

