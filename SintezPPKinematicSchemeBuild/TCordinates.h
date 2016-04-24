#pragma once
#include <vector>

namespace pss
{
	class TCordinates
	{
	public:
		TCordinates( int x, int y );
		int										m_x = 0;
		int										m_y = 0;

		TCordinates								getLeftNeighbor() const;
		TCordinates								getRightNeighbor( ) const;
		TCordinates								getTopNeighbor( ) const;
		TCordinates								getBottomNeighbor( ) const;
		std::vector<TCordinates>				getNeighbors( ) const;
		friend bool								operator<( const TCordinates & cord1, const TCordinates& cord2 );
	};
}


