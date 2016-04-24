#pragma once

#include "TPlanetaryGearSet.h"

namespace pss
{
	class TKinematicScheme
	{
	private:
		std::vector<TPlanetaryGearSet>						m_field;
	public:
		std::vector<pss::TChain>&				operator[]( int xPos );
		void									addGearSet(const TPlanetaryGearSet & gearSet);
		void									print();
	};
}


