#pragma once

#include <vector>

#include "TGearBox.h"
#include "../Libraries/TLink.h"
#include "../Libraries/TChainsContainer.h"
#include "../Libraries/GlobalDefines.h"


NS_ARI_START

class TGenerate
{
private:
	std::vector<NS_CORE TLink>					m_allLinks;
	NS_CORE TChainsContainer					m_existingSchemes;

	void										readInitialData();
	void										generateInOut();
	void										generateLinks( const TGearBox & gearBox );
	void										generateFrictions( const TGearBox & gearBox );
	void										generateBrakes( const TGearBox & gearBox );

public:

	void										generate();

};

NS_ARI_END