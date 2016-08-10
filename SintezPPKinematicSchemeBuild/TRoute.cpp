#include "TRoute.h"


size_t pss::TRoute::size()
{
	return m_route.size();
}

void pss::TRoute::addCordinates( const pss::TCordinates & cordinates )
{
	m_route.emplace_back( cordinates );
}

pss::TCordinates pss::TRoute::operator[]( size_t pos )
{
	return m_route.at( pos );
}
