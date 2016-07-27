#pragma once

#include <vector>
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TCode.h"
#include "../Libraries/GlobalDefines.h"

namespace pss{

	class DefK
	{
	public:

		TK										findK(const TCode& Code);
		void									run();

	private:

		void									readInitialData();

		void									checkAllInitialKValues( const TCode& Code, TK& ret );
		void									checkAllRatiosPermutations( const TCode& Code, const TK& initial, TK& ret );
	};

}