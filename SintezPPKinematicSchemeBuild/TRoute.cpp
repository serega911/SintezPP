#include "TRoute.h"

NS_ARI_USING

size_t TRoute::size()
{
	return m_route.size();
}

void TRoute::addCordinates( const TCordinates & cordinates )
{
	m_route.emplace_back( cordinates );
}

TCordinates TRoute::operator[]( size_t pos )
{
	return m_route.at( pos );
}
