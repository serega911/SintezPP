#include <iostream>
#include "TPathBuilder.h"


int main()
{
	pss::TKinematicScheme scheme;
	pss::TPlanetaryGearSet set;
	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_N );
	scheme.addGearSet(set);

	set.create( 2, pss::TPlanetaryGearSet::Type::TYPE_N_REVERSE );
	scheme.addGearSet( set );

	set.create( 3, pss::TPlanetaryGearSet::Type::TYPE_U );
	scheme.addGearSet( set );

	set.create( 4, pss::TPlanetaryGearSet::Type::TYPE_U_REVERSE );
	scheme.addGearSet( set );

	set.create( 5, pss::TPlanetaryGearSet::Type::TYPE_DEFAULT );
	scheme.addGearSet( set );

	scheme.print();
	system( "pause" );
	pss::TPathBuilder pathBuilder;
	pathBuilder.findPath( scheme, pss::TLink( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), 1 ),
												pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), 2 ) ) );

	system("pause");
}