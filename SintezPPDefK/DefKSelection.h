#pragma once

#include <vector>

#include "InternalGearRatios.h"
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
	static NS_CORE Ratios						podModul( const NS_CORE Code & code, const NS_ARI InternalGearRatios &k );
	static size_t								countOfDifferent( const NS_CORE Ratios& i);

};

NS_ARI_END