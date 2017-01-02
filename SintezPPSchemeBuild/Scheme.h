#pragma once

#include <vector>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Code.h"

#include "Link.h"
#include "GearSet.h"
#include "Display.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/Link.h"

NS_ARI_START

class Scheme
{
private:

	static const int s_setWidth;
	static const int s_height;

	int											m_width;
	std::vector<Link_p>							m_links;
	std::vector<ISchemeElement_p>				m_staticElements;

	void										printElement( NS_ARI ISchemeElement_p set, const Display& disp );

public:

	Scheme( const NS_CORE InternalGearRatios k );

	void										print( const Display& disp );

	void										clear();
	void										addLink( const std::vector<Cordinate>& trace, const NS_CORE Link& link );
	void										addFriction( const std::vector<Cordinate>& trace, const NS_CORE Link& link );

};



NS_ARI_END