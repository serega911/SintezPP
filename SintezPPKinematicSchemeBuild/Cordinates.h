#pragma once
#include <map>
#include <vector>
#include "eDirection.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

struct Cordinates;
typedef std::vector<Cordinates> TCordinatesArray;

struct Cordinates
{
	Cordinates( int x, int y );
	Cordinates();

	int											m_x;
	int											m_y;

	Cordinates									getLeftNeighbor() const;
	Cordinates									getRightNeighbor() const;
	Cordinates									getTopNeighbor() const;
	Cordinates									getBottomNeighbor() const;

	std::map<eDirection, Cordinates>			getNeighbors() const;

	friend bool									operator<( const Cordinates & cord1, const Cordinates& cord2 );
};

NS_ARI_END


