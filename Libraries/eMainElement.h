#pragma once

#include "enum.h"

namespace pss
{
	BETTER_ENUM( eMainElement, int
		,EMPTY = 0
		,SUN_GEAR
		,EPICYCLIC_GEAR
		,CARRIER
		,INPUT					
		,OUTPUT
		,BRAKE
		,BUSY
	);
}