#include <iostream>
#include "TPathBuilder.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/IContainer.h"


int main()
{
// 	pss::TKinematicScheme scheme;
// 	pss::TPlanetaryGearSet set;
// 	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_N );
// 	scheme.addGearSet(set);
// 
// 	set.create( 2, pss::TPlanetaryGearSet::Type::TYPE_N_REVERSE );
// 	scheme.addGearSet( set );
// 
// 	set.create( 3, pss::TPlanetaryGearSet::Type::TYPE_U );
// 	scheme.addGearSet( set );
// 
// 	set.create( 4, pss::TPlanetaryGearSet::Type::TYPE_U_REVERSE );
// 	scheme.addGearSet( set );
// 
// 	set.create( 5, pss::TPlanetaryGearSet::Type::TYPE_DEFAULT );
// 	scheme.addGearSet( set );
// 
// 	scheme.addBorders();
// 
// 	scheme.print();
// 	system( "pause" );
// 	pss::TPathBuilder pathBuilder;
//	pathBuilder.findPath( scheme, pss::TLink( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), 1 ),
//												pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), 2 ) ) );

	pss::TCode code;
	pss::TK k;
	std::vector<pss::IContainer*> containers;
	containers.push_back( &code );
	containers.push_back( &k );

	pss::TSingletons::getInstance()->setGlobalParameters( 2, 2 );


	while ( pss::TSingletons::getInstance()->getLoaderFromFile()->load( containers, pss::TIOFileManager::eOutputFileType::DONE_K ) )
	{
		code.print();
		k.print();
	}

	system("pause");
}