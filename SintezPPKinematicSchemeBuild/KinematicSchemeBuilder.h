#pragma once

#include "KinematicScheme.h"
#include"../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/KinematicSchemeData.h"

NS_ARI_START

class KinematicSchemeBuilder
	: public NS_CORE ApplicationBase
{

private:

	void										readUISpecialData();
	KinematicScheme								creatKinematicScheme( const core::Code & code, const core::InternalGearRatios & k );
	PlanetaryGearSet::Type						getPlanetaryGearSetType( const NS_CORE InternalGearRatioValue& k );

	NS_CORE KinematicSchemeData					calcKinemaricSchemeCharacteristics( const KinematicScheme& scheme );

	NS_CORE KinematicSchemeData					bildSchemeSlow( const core::Code & code, const core::InternalGearRatios & k );
	NS_CORE KinematicSchemeData					bildSchemeQuick( const core::Code & code, const core::InternalGearRatios & k );

public:

	void										run() override;

};

NS_ARI_END