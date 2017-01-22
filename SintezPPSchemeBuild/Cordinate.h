#pragma once
#include <map>
#include <vector>
#include "eDirection.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

struct Cordinate
{
	typedef std::map<eDirection, Cordinate> Neighbors;

	Cordinate( int x, int y );
	Cordinate();

	int											m_x;
	int											m_y;

	Cordinate									getLeftNeighbor() const;
	Cordinate									getRightNeighbor() const;
	Cordinate									getTopNeighbor() const;
	Cordinate									getBottomNeighbor() const;

	Neighbors									get4Neighbors() const;
	Neighbors									get8Neighbors() const;

	friend Cordinate							operator+( const Cordinate & cord1, const Cordinate& cord2 );
	friend Cordinate							operator-( const Cordinate & cord1, const Cordinate& cord2 );
	friend bool									operator<( const Cordinate & cord1, const Cordinate& cord2 );
};

NS_ARI_END


