#pragma once
#include <map>
#include "eDirection.h"

namespace pss
{
	class TCordinates
	{
	public:
		TCordinates( int x, int y );
		TCordinates();
		int										m_x ;
		int										m_y;

		TCordinates								getLeftNeighbor() const;
		TCordinates								getRightNeighbor( ) const;
		TCordinates								getTopNeighbor( ) const;
		TCordinates								getBottomNeighbor( ) const;
		std::map<eDirection, TCordinates>		getNeighbors( ) const;
		friend bool								operator<( const TCordinates & cord1, const TCordinates& cord2 );
	};
}


