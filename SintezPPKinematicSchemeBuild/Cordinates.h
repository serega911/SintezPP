#pragma once
#include <map>
#include <vector>
#include "eDirection.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

struct Cordinate;
typedef std::vector<Cordinate> TCordinatesArray;

struct Cordinate
{
	Cordinate( int x, int y );
	Cordinate();

	int											m_x;
	int											m_y;

	Cordinate									getLeftNeighbor() const;
	Cordinate									getRightNeighbor() const;
	Cordinate									getTopNeighbor() const;
	Cordinate									getBottomNeighbor() const;

	std::map<eDirection, Cordinate>			get4Neighbors() const;

	friend bool									operator<( const Cordinate & cord1, const Cordinate& cord2 );
};

NS_ARI_END


