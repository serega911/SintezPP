#pragma once
#include "GearSet.h"
#include "eGearSetType.h"

NS_ARI_START

class GearSetFactory
{
private:

	GearSet										createStandart();
	GearSet										createCustom( const bool flipX, const bool flipY );


public:
	GearSetFactory();
	~GearSetFactory();

	GearSet										createGearSet( eGearSetType type );
};

NS_CORE_END