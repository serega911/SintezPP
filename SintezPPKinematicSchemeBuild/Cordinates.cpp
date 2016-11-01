#include "Cordinates.h"

NS_ARI_USING

Cordinates::Cordinates( int x, int y )
	: m_x( x )
	, m_y( y )
{
}

Cordinates::Cordinates() : Cordinates( 0, 0 )
{
}

Cordinates Cordinates::getLeftNeighbor() const
{
	return Cordinates( m_x - 1, m_y );
}

Cordinates Cordinates::getRightNeighbor( ) const
{
	return Cordinates( m_x + 1, m_y );
}

Cordinates Cordinates::getTopNeighbor( ) const
{
	return Cordinates( m_x, m_y + 1 );
}

Cordinates Cordinates::getBottomNeighbor( ) const
{
	return Cordinates( m_x, m_y - 1 );
}

std::map<eDirection, Cordinates> Cordinates::getNeighbors( ) const
{
	std::map<eDirection, Cordinates> neighbors;

	neighbors[eDirection::LEFT] =  getLeftNeighbor( );
	neighbors[eDirection::RIGHT] = getRightNeighbor( );
	neighbors[eDirection::UP] = getTopNeighbor( );
	neighbors[eDirection::DOWN] = getBottomNeighbor( );

	return neighbors;
}

bool NS_ARI operator<( const Cordinates & cord1, const Cordinates& cord2 )
{
	return cord1.m_x == cord2.m_x ? cord1.m_y < cord2.m_y : cord1.m_x < cord2.m_x;
		
}