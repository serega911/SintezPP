#include "Link.h"

NS_ARI_USING


void ari::Link::addCord( const Cordinate& cord )
{
	m_cells.emplace_back( LinkCell::create( cord, this ) );
}

bool ari::Link::isConsist( const NS_CORE Element& elem )
{
	return m_elements.find( elem ) != m_elements.end();
}

const ISchemeElement::Cordinates& ari::Link::getCordsWorldSpace() const
{
	return m_cells;
}

void ari::Link::addElem( const NS_CORE Element& elem )
{
	m_elements.insert( elem );
}

Link_p ari::Link::create()
{
	return Link_p( new Link );
}
