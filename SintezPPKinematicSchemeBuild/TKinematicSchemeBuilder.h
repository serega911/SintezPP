#pragma once

#include "TKinematicScheme.h"
#include"../Libraries/GlobalDefines.h"

NS_ARI_START

class TKinematicSchemeBuilder
{

private:

	void										readInitialData();
	TKinematicScheme							creatKinematicScheme( const core::TCode & code, const core::TK & k );
	TPlanetaryGearSet::Type						getPlanetaryGearSetType( const NS_CORE TKValue& k );

public:

	void										buildSchemes();

};

NS_ARI_END