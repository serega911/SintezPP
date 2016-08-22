#pragma once

#include <vector>

#include "TGearBox.h"
#include "../Libraries/TLink.h"
#include "../Libraries/TChainsContainer.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/IApplication.h"


NS_ARI_START

class TGenerate
	: public NS_CORE IApplication
{
private:

	static const std::vector<NS_CORE eMainElement>	s_elements;

	std::vector<NS_CORE TLink>					m_allLinks;
	NS_CORE TChainsContainer					m_existingSchemes;

	void										readInitialData() override;
	void										generateInOut();
	void										generateLinks( const TGearBox & gearBox );
	void										generateFrictions( const TGearBox & gearBox );
	void										generateBrakes( const TGearBox & gearBox );

public:

	void										run() override;

};

NS_ARI_END