#include "Link.h"

NS_ARI_USING


void ari::Link::addCord( const Cordinate& cord )
{
	ISchemeCell_p cell(new LinkCell(cord, this));
	m_cells.emplace_back( cell );
}

bool ari::Link::isConsist( const NS_CORE eMainElement& elem )
{
	return m_elements.find( elem ) != m_elements.end();
}

const ISchemeElement::Cordinates& ari::Link::getCordsWorldSpace() const
{
	return m_cells;
}
