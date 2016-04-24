#include "TCordinates.h"

pss::TCordinates::TCordinates( int x, int y ) : 
m_x( x ), m_y( y )
{

}

pss::TCordinates pss::TCordinates::getLeftNeighbor( ) const
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

std::vector<pss::TCordinates> pss::TCordinates::getNeighbors( ) const
{
	std::vector<pss::TCordinates> neighbors;
	neighbors.push_back( getLeftNeighbor( ) );
	neighbors.push_back( getRightNeighbor( ) );
	neighbors.push_back( getTopNeighbor( ) );
	neighbors.push_back( getBottomNeighbor( ) );
	return neighbors;
}

bool pss::operator<( const pss::TCordinates & cord1, const pss::TCordinates& cord2 )
{
	if ( cord1.m_x == cord2.m_x )
		return cord1.m_y < cord2.m_y;
	else
		return cord1.m_x < cord2.m_x;
}