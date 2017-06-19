#include "Link.h"

NS_ARI_USING


void ari::Link::addCord( const Cordinate& cord )
{
	m_cells.emplace_back( LinkCell::create( cord, this ) );
}

bool ari::Link::isConsist( const NS_CORE Element& elem )
{
	return m_elements.find( elem );
}

const ISchemeElement::Cordinates& ari::Link::getCordsWorldSpace() const
{
	return m_cells;
}

void ari::Link::addElem( const NS_CORE Element& elem )
{
	m_elements.addElementToChain( elem );
}

Link_p ari::Link::create()
{
	return Link_p( new Link );
}

const NS_CORE MultiLink& ari::Link::getElements() const
{
	return m_elements;
}

void ari::Link::addChain( const NS_CORE MultiLink& chain )
{
	m_elements.addChainToChain( chain );
}

void ari::Link::addLink( const NS_CORE Link& link )
{
	m_elements.addLinkToChain( link );
}
