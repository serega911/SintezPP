#pragma once

#include <vector>

#include "InternalGearRatios.h"
#include "../Libraries/GearBoxWithChanger.h"
#include "../Libraries/InternalGearRatioArray.h"
#include "../Libraries/RatiosArray.h"
#include "../Libraries/Code.h"
#include "../Libraries/Ratios.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class DefKSelection
{
public:

	NS_CORE InternalGearRatioArray				calculate( const NS_CORE Code& code );
	static NS_CORE Ratios						podModul( NS_CORE GearBoxWithChanger & gb, const NS_ARI InternalGearRatios &k );
	static size_t								countOfDifferent( const NS_CORE Ratios& i, const float eps );

};

NS_ARI_END