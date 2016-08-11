#include "TKinematicSchemeBuilder.h"
#include <iostream>
#include "TPathBuilder.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/IContainer.h"

pss::TKinematicScheme pss::TKinematicSchemeBuilder::creatKinematicScheme( const core::TCode & code, const core::TK & k )
{
	pss::TKinematicScheme scheme;
	pss::TPlanetaryGearSet set;
	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_DEFAULT );
	scheme.addGearSet( set );
	set.create( 2, pss::TPlanetaryGearSet::Type::TYPE_DEFAULT );
	scheme.addGearSet( set );
	scheme.addBorders();
	return scheme;
}

void pss::TKinematicSchemeBuilder::buildSchemes()
{
	core::TSingletons::getInstance()->setGlobalParameters( 2, 2 );
	core::TCode code;
	core::TK k;
	std::vector<core::IContainer*> containers;
	containers.push_back( &code );
	containers.push_back( &k );

	while ( core::TSingletons::getInstance()->getLoaderFromFile()->load( containers, core::TIOFileManager::eOutputFileType::DONE_K ) )
	{
		pss::TKinematicScheme scheme = creatKinematicScheme(code,k);

		system( "cls" );
		scheme.print();
		//system( "pause" );

		const auto& elements = code.getCode();

		for ( int i = 0; i < elements.size(); i++ )
		{
			pss::TPathBuilder pathBuilder;
			auto path = pathBuilder.findPath( scheme, elements[i] );
			if ( path.size() != 0 )
			{
				scheme.addRoute( path, elements[i] );
			}
			system( "cls" );
			scheme.print();
			//system( "pause" );
		}
		code.print();
		k.print();
	}
}

