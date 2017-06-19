#pragma once

#include <vector>

#include "GearBox.h"
#include "../Libraries/Link.h"
#include "../Libraries/MultiLinkContainer.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/eMainElementArray.h"


NS_ARI_START

class Generate
	: public NS_CORE ApplicationBase
{
private:

	static const NS_CORE eMainElementArray	s_elements;

	NS_CORE TLinkArray							m_allLinks;
	NS_CORE MultiLinkContainer						m_existingSchemes;


	void										generateInOut();
	void										generateLinks( const GearBox & gearBox );
	void										generateFrictions( const GearBox & gearBox );
	void										generateBrakes( const GearBox & gearBox );

public:

	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END