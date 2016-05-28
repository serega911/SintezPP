#pragma once

#include <vector>

#include "Fumction.h"

namespace pss
{
	class Equations
	{
	private:

		static value							dfDk( variable k, variable w1, variable w2, variable w3 );
		static value							dfDw1( variable k, variable w1, variable w2, variable w3 );
		static value							dfDw2( variable k, variable w1, variable w2, variable w3 );
		static value							dfDw3( variable k, variable w1, variable w2, variable w3 );
		
	public:

		static const std::vector<const equation>s_equations;

		static value							wyllys( variable k, variable w1, variable w2, variable w3 );

		static value							empty( variable k, variable w1, variable w2, variable w3 );

	};
}