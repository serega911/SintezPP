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

std::map<eDirection, Cordinate> Cordinate::getNeighbors( ) const
{
	std::map<eDirection, Cordinate> neighbors;

	neighbors[eDirection::LEFT] =  getLeftNeighbor( );
	neighbors[eDirection::RIGHT] = getRightNeighbor( );
	neighbors[eDirection::UP] = getTopNeighbor( );
	neighbors[eDirection::DOWN] = getBottomNeighbor( );

	return neighbors;
}

std::vector<Cordinate> ari::Cordinate::get8Neighbors() const
{
	std::vector<Cordinate> ret;

	ret.emplace_back( Cordinate(m_x - 1, m_y - 1) );
	ret.emplace_back( Cordinate(m_x - 1, m_y) );
	ret.emplace_back( Cordinate(m_x - 1, m_y + 1) );
	ret.emplace_back( Cordinate(m_x, m_y - 1) );
	ret.emplace_back( Cordinate(m_x, m_y + 1) );
	ret.emplace_back( Cordinate(m_x + 1, m_y - 1) );
	ret.emplace_back( Cordinate(m_x + 1, m_y) );
	ret.emplace_back( Cordinate(m_x + 1, m_y + 1) );

	return ret;
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