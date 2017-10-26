#pragma once

#include <map>

#include "GlobalDefines.h"
#include "GearBox.h"
#include "GearChanger.h"

NS_CORE_START

class GearBoxWithChanger
	: public NS_CORE GearBox
{
private:

	std::map<size_t, NS_CORE MultiLinkArray>	m_gearsChains;
	void										createGear();

protected:

	typedef NS_CORE GearBox Parent;

	size_t										m_gear;
	NS_CORE GearChanger							m_gearChanger;

public:

	GearBoxWithChanger( const NS_CORE Code& code );

	virtual NS_CORE MultiLinkArray				getChainsForCurrentGear() const;

	bool										turnOnNextGear();
	void										reset();

};

NS_CORE_END
