#pragma once

#include <memory>

#include "../Libraries/InternalGearRatioValue.h"


#include "GearSet.h"
#include "Cordinate.h"
#include "eGearSetType.h"


NS_ARI_START

class GearSetFactory
{
private:

	static eGearSetType							getType( const NS_CORE InternalGearRatioValue ratio );
	static GearSet_p							createStandart( const Cordinate& anchor );
	static GearSet_p							createCustom( const Cordinate& anchor, const bool flipX, const bool flipY );

public:

	static GearSet_p							createGearSet( const NS_CORE InternalGearRatioValue ratio, const Cordinate& anchor );

};

NS_CORE_END