#include <iostream>

#include "../Libraries/SchemeCharacteristics.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/CombinatoricsValueArray.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/IIOItem.h"

#include "KinematicSchemeBuilder.h"
#include "SchemeBuilderSwapPrev.h"
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

	while ( core::Singletons::getInstance()->getLoaderFromFile()->load( containers, core::IOFileManager::eOutputFileType::DONE_K ) )
	{
		IScheme_p scheme = Scheme::create( k );
		NS_ARI ITraceStrategy_p pathBuilder = NS_ARI PathBuilderLee::create();
		NS_ARI ISchemeBuildStartegy_p schemeBuilder = NS_ARI SchemeBuilderSwapPrev::create();

		if ( schemeBuilder->run( scheme, pathBuilder, code ) )
		{
			NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW, code );
		}
	}
}

