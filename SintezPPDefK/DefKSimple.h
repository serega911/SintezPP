#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/InternalGearRatioArray.h"
#include "../Libraries/RatiosArray.h"
#include "../Libraries/Ratios.h"

#include "System.h"


NS_ARI_START

class DefKSimple
{
private:

	NS_CORE InternalGearRatios					findK( const NS_CORE Code& code, const NS_CORE InternalGearRatios& initialKValues, const NS_CORE Ratios& iTarget );
	NS_CORE InternalGearRatios					solveSimple( System& system );
	NS_CORE InternalGearRatios					getInternalGearRatioValuesFromSystem( const System & system );
	bool										isAllKValuesFinded( const System & system );

public:

	DefKSimple();

	NS_CORE InternalGearRatioArray				calculate( const NS_CORE Code& code );

};

NS_ARI_END