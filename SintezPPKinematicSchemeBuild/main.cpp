#include <iostream>
#include "TKinematicScheme.h"

int main()
{
	pss::TKinematicScheme scheme;
	pss::TPlanetaryGearSet set;
	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_N );
	scheme.addGearSet(set);

	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_N_REVERSE );
	scheme.addGearSet( set );

	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_U );
	scheme.addGearSet( set );

	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_U_REVERSE );
	scheme.addGearSet( set );

	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_DEFAULT );
	scheme.addGearSet( set );

	scheme.print();

	system("pause");
}