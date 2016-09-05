#pragma once

#include <vector>

#include "TLink.h"
#include "TCode.h"
#include "GlobalDefines.h"

NS_CORE_START

class TGearChanger
{
private:

	TLinkArray									m_drivingElements;
	std::vector<TLinkArray>						m_drivingElementsForAllGears;
	size_t										m_gear;

public:

	TGearChanger() = delete;
	TGearChanger(const TCode& code);

	TLinkArray									getDrivingElementsForGear() const;
	bool										next();

};

NS_CORE_END