#include "TCordinates.h"

NS_ARI_USING

TCordinates::TCordinates( int x, int y )
	: m_x( x )
	, m_y( y )
{
}

TCordinates::TCordinates() : TCordinates( 0, 0 )
{
}

TCordinates TCordinates::getLeftNeighbor() const
{
	return TCordinates( m_x - 1, m_y );
}

TCordinates TCordinates::getRightNeighbor( ) const
{
	return TCordinates( m_x + 1, m_y );
}

TCordinates TCordinates::getTopNeighbor( ) const
{
	return TCordinates( m_x, m_y + 1 );
}

TCordinates TCordinates::getBottomNeighbor( ) const
{
	return TCordinates( m_x, m_y - 1 );
}

std::map<eDirection, TCordinates> TCordinates::getNeighbors( ) const
{
	std::map<eDirection, TCordinates> neighbors;

	neighbors[eDirection::LEFT] =  getLeftNeighbor( );
	neighbors[eDirection::RIGHT] = getRightNeighbor( );
	neighbors[eDirection::UP] = getTopNeighbor( );
	neighbors[eDirection::DOWN] = getBottomNeighbor( );

	return neighbors;
}

bool NS_ARI operator<( const TCordinates & cord1, const TCordinates& cord2 )
{
	return cord1.m_x == cord2.m_x ? cord1.m_y < cord2.m_y : cord1.m_x < cord2.m_x;
		
}