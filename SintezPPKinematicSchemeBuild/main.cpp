#include <iostream>
#include "TPlanetaryGearSet.h"

int main()
{
	pss::TPlanetaryGearSet set;
	set.create( 1, pss::TPlanetaryGearSet::Type::TYPE_N_REVERSE );
	set.print();
	system("pause");
}