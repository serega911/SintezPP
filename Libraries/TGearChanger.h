#pragma once

#include "../Libraries/TLink.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TReplace.h"
#include <vector>


namespace pss
{
	class TGearChanger
	{
	private:
		std::vector<pss::TLink>					m_drivingElements;
		pss::TReplace							m_replacer;

		std::vector<pss::TLink>					createVector(const pss::TReplace & replacer) const;
	public:
		TGearChanger() = delete;
		TGearChanger(const pss::TCode& code);

		std::vector<pss::TLink>					getDrivingElementsForGear(int gear) const;
		std::vector<pss::TLink>					getDrivingElementsForGear() const;
		bool									next();

	};

}