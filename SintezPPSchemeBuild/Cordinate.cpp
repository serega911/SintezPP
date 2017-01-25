#include "Cordinate.h"

NS_ARI_USING

Cordinate::Cordinate( int x, int y )
	: m_x( x )
	, m_y( y )
{
}

Cordinate::Cordinate() : Cordinate( 0, 0 )
{
}

Cordinate Cordinate::getLeftNeighbor() const
{
	return Cordinate( m_x - 1, m_y );
}

Cordinate Cordinate::getRightNeighbor( ) const
{
	return Cordinate( m_x + 1, m_y );
}

Cordinate Cordinate::getTopNeighbor( ) const
{
	return Cordinate( m_x, m_y + 1 );
}

Cordinate Cordinate::getBottomNeighbor( ) const
{
	return Cordinate( m_x, m_y - 1 );
}

Cordinate::Neighbors Cordinate::get4Neighbors() const
{
	Neighbors neighbors;

	neighbors[eDirection::LEFT] =  getLeftNeighbor( );
	neighbors[eDirection::RIGHT] = getRightNeighbor( );
	neighbors[eDirection::UP] = getTopNeighbor( );
	neighbors[eDirection::DOWN] = getBottomNeighbor( );

	return neighbors;
}

Cordinate::Neighbors ari::Cordinate::get8Neighbors() const
{
	Neighbors neighbors = get4Neighbors();

	const auto & top = neighbors[eDirection::UP];
	const auto & bottom = neighbors[eDirection::DOWN];

	neighbors[eDirection::UP_LEFT] = top.getLeftNeighbor();
	neighbors[eDirection::UP_RIGHT] = top.getRightNeighbor();
	neighbors[eDirection::DOWN_LEFT] = bottom.getLeftNeighbor();
	neighbors[eDirection::DOWN_RIGHT] = bottom.getRightNeighbor();

	return neighbors;
}

bool NS_ARI operator<( const Cordinate & cord1, const Cordinate& cord2 )
{
	return cord1.m_x == cord2.m_x ? cord1.m_y < cord2.m_y : cord1.m_x < cord2.m_x;	
}

Cordinate NS_ARI operator+( const Cordinate & cord1, const Cordinate& cord2 )
{
	return Cordinate( cord1.m_x + cord2.m_x, cord1.m_y + cord2.m_y );
}

Cordinate NS_ARI operator-( const Cordinate & cord1, const Cordinate& cord2 )
{
	return Cordinate( cord1.m_x - cord2.m_x, cord1.m_y - cord2.m_y );
}