#include "TKinematicSchemeBuilder.h"
#include <iostream>
#include "TPathBuilder.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/IContainer.h"

pss::TKinematicScheme pss::TKinematicSchemeBuilder::creatKinematicScheme( const pss::TCode & code, const pss::TK & k )
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
	pss::TSingletons::getInstance()->setGlobalParameters( 2, 2 );
	pss::TCode code;
	pss::TK k;
	std::vector<pss::IContainer*> containers;
	containers.push_back( &code );
	containers.push_back( &k );

	while ( pss::TSingletons::getInstance()->getLoaderFromFile()->load( containers, pss::TIOFileManager::eOutputFileType::DONE_K ) )
	{
		pss::TKinematicScheme scheme = creatKinematicScheme(code,k);

		system( "cls" );
		scheme.print();
		//system( "pause" );

		for ( int i = 0; i < code.size(); i++ )
		{
			pss::TPathBuilder pathBuilder;
			auto path = pathBuilder.findPath( scheme, code[i] );
			if ( path.size() != 0 )
			{
				scheme.addRoute( path, code[i] );
			}
			system( "cls" );
			scheme.print();
			//system( "pause" );
		}
		code.print();
		k.print();
	}
}

