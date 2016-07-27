#pragma once

#include "../Libraries/TLink.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TCombinations.h"
#include <vector>


namespace pss
{
	class TGearChanger
	{
	private:
		std::vector<pss::TLink>					m_drivingElements;
		pss::TCombinations							m_replacer;

		std::vector<pss::TLink>					createVector(const pss::TCombinations & replacer) const;
	public:
		TGearChanger() = delete;
		TGearChanger(const pss::TCode& code);

		std::vector<pss::TLink>					getDrivingElementsForGear(int gear) const;
		std::vector<pss::TLink>					getDrivingElementsForGear() const;
		bool									next();

	};

}