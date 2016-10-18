#pragma once

#include <vector>

#include "TGearBox.h"
#include "../Libraries/TLink.h"
#include "../Libraries/TChainsContainer.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"


NS_ARI_START

class TGenerate
	: public NS_CORE ApplicationBase
{
private:

	static const NS_CORE eMainElementArray	s_elements;

	NS_CORE TLinkArray							m_allLinks;
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