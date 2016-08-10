#pragma once

#include "TPlanetaryGearSet.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "TCordinates.h"
#include <vector>

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
		void									addRoute( const std::vector<pss::TCordinates> & cord, const pss::TLink & link );
		void									addBorders();
		void									print();

		void									create( const pss::TCode& code, pss::TK & k );
		size_t									size() const;

	};
}


