#pragma once

#include <vector>

#include "TLink.h"
#include "TCode.h"
#include "TCombinations.h"
#include "GlobalDefines.h"

NS_CORE_START

class TGearChanger
{
private:

	TLinkArray									m_drivingElements;
	TCombinations								m_replacer;

	std::vector<TLinkArray>						m_drivingElementsForAllGears;
	size_t										m_gear;

	//TLinkArray									createVector( const TCombinations & replacer ) const;

public:

	TGearChanger() = delete;
	TGearChanger(const TCode& code);

	TLinkArray									getDrivingElementsForGear() const;
	bool										next();

};

NS_CORE_END