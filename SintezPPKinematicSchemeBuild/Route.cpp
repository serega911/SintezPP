#include "Route.h"

NS_ARI_USING

size_t Route::size()
{
	return m_route.size();
}

void Route::addCordinates( const Cordinates & cordinates )
{
	m_route.emplace_back( cordinates );
}

Cordinates Route::operator[]( size_t pos )
{
	return m_route.at( pos );
}
