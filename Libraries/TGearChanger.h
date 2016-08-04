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

	std::vector<TLink>							m_drivingElements;
	TCombinations								m_replacer;

	std::vector<TLink>							createVector(const TCombinations & replacer) const;

public:

	TGearChanger() = delete;
	TGearChanger(const TCode& code);

//	std::vector<TLink>							getDrivingElementsForGear(int gear) const;
	std::vector<TLink>							getDrivingElementsForGear() const;
	bool										next();

};

NS_CORE_END