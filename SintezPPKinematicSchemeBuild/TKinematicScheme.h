#pragma once

#include "TPlanetaryGearSet.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"

namespace pss
{
	class TKinematicScheme
	{
	private:
		std::vector<TPlanetaryGearSet>			m_field;
		pss::TCode								m_code;
		pss::TK									m_k;
	public:
		const std::vector<pss::TChain>&				operator[]( int xPos ) const;
		std::vector<pss::TChain>&				operator[]( int xPos );
		void									addGearSet(const TPlanetaryGearSet & gearSet);
		void									print();

		void									create( const pss::TCode& code, pss::TK & k );
		size_t									size() const;

	};
}


