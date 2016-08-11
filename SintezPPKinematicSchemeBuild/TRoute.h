#pragma once

#include "TCordinates.h"
#include <vector>

namespace pss
{
	class TRoute
	{
	private:
		std::vector<pss::TCordinates>			m_route;
	public:
		size_t									size();
		void									addCordinates( const pss::TCordinates & cordinates);
		pss::TCordinates						operator[](size_t pos);
	};
}


