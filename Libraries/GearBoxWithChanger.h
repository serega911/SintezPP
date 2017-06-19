#pragma once

#include "GlobalDefines.h"
#include "GearBox.h"
#include "GearChanger.h"

NS_CORE_START

class GearBoxWithChanger
	: public NS_CORE GearBox
{
protected:

	typedef NS_CORE GearBox Parent;

	NS_CORE GearChanger							m_gearChanger;

public:

	GearBoxWithChanger( const NS_CORE Code& code );

	virtual NS_CORE MultiLinkArray					getChainsForCurrentGear() const;

	bool										turnOnNextGear();

};

NS_CORE_END
