#pragma once
#include <map>
#include <vector>
#include "eDirection.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

struct TCordinates;
typedef std::vector<TCordinates> TCordinatesArray;

struct TCordinates
{
	TCordinates( int x, int y );
	TCordinates();

	int											m_x;
	int											m_y;

	TCordinates									getLeftNeighbor() const;
	TCordinates									getRightNeighbor() const;
	TCordinates									getTopNeighbor() const;
	TCordinates									getBottomNeighbor() const;

	std::map<eDirection, TCordinates>			getNeighbors() const;

	friend bool									operator<( const TCordinates & cord1, const TCordinates& cord2 );
};

NS_ARI_END


