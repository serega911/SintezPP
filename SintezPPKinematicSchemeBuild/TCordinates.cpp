#include "TCordinates.h"

pss::TCordinates::TCordinates( int x, int y ) : 
m_x( x ), m_y( y )
{

}

pss::TCordinates::TCordinates() : TCordinates( 0, 0 )
{

}

pss::TCordinates pss::TCordinates::getLeftNeighbor() const
{
	return pss::TCordinates( m_x - 1, m_y );
}

pss::TCordinates pss::TCordinates::getRightNeighbor( ) const
{
	return pss::TCordinates( m_x + 1, m_y );
}

pss::TCordinates pss::TCordinates::getTopNeighbor( ) const
{
	return pss::TCordinates( m_x, m_y + 1 );
}

pss::TCordinates pss::TCordinates::getBottomNeighbor( ) const
{
	return pss::TCordinates( m_x, m_y - 1 );
}

std::map<pss::eDirection, pss::TCordinates> pss::TCordinates::getNeighbors( ) const
{
	std::map<pss::eDirection, pss::TCordinates> neighbors;
	neighbors[pss::eDirection::LEFT] =  getLeftNeighbor( );
	neighbors[pss::eDirection::RIGHT] = getRightNeighbor( );
	neighbors[pss::eDirection::UP] = getTopNeighbor( );
	neighbors[pss::eDirection::DOWN] = getBottomNeighbor( );
	return neighbors;
}

bool pss::operator<( const pss::TCordinates & cord1, const pss::TCordinates& cord2 )
{
	if ( cord1.m_x == cord2.m_x )
		return cord1.m_y < cord2.m_y;
	else
		return cord1.m_x < cord2.m_x;
}