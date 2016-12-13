#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/GearBox.h"
#include "../Libraries/GearChanger.h"

NS_ARI_START

class GearBox
	: public NS_CORE GearBox
{
private:

	typedef NS_CORE GearBox Parent;

	NS_CORE GearChanger							m_gearChanger;

public:

	GearBox( const NS_CORE Code& code );

	NS_CORE ChainArray							getChainsForCurrentGear() const;

	bool										turnOnNextGear();

};

NS_ARI_END
