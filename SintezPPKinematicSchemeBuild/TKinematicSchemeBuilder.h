#pragma once

#include "TKinematicScheme.h"
#include"../Libraries/GlobalDefines.h"
#include "../Libraries/IApplication.h"
#include "../Libraries/KinematicSchemeData.h"

NS_ARI_START

class TKinematicSchemeBuilder
	: public NS_CORE IApplication
{

private:

	void										readInitialData() override;
	TKinematicScheme							creatKinematicScheme( const core::TCode & code, const core::TK & k );
	TPlanetaryGearSet::Type						getPlanetaryGearSetType( const NS_CORE TKValue& k );

	NS_CORE KinematicSchemeData					calcKinemaricSchemeCharacteristics( const TKinematicScheme& scheme );

	NS_CORE KinematicSchemeData					bildSchemeSlow( const core::TCode & code, const core::TK & k );
	NS_CORE KinematicSchemeData					bildSchemeQuick( const core::TCode & code, const core::TK & k );

public:

	void										run() override;

};

NS_ARI_END