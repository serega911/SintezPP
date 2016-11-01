#include "Chain.h"
#include "Singletons.h"
#include <algorithm>

core::Chain::Chain( const Element& element )
{
	addElementToChain( element );
}

NS_CORE_USING

Chain::Chain()
{
}

void Chain::addLinkToChain(const Link & link)
{
	m_elements.insert(link.getElem1());
	m_elements.insert(link.getElem2());
}

void Chain::addElementToChain(const Element & elem)
{
	m_elements.insert(elem);
}

void Chain::addChainToChain(const Chain & chain)
{
	for (auto& it : chain.m_elements)
		m_elements.insert(it);
}

void Chain::clear()
{
	m_elements.clear();
}

bool Chain::find(const Element & element) const
{
	if ( m_elements.find( element ) != m_elements.end() )
		return true;
	else
		return false;
}

bool Chain::checkElemByOnePlanetarySet() const
{
	const GearSetNumber N (Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears);
	for (GearSetNumber i (1); i <= N; i++)
	{
		int count = 0;
		for (auto &it : m_elements)
		{
			if (it.getGearSetN() == i)
				count++;
		}
		if (count > 1)
		{
			return false;
		}
	}
	return true;
}

const Element& Chain::getSomeElement() const
{
	for ( const auto& it : m_elements )
	{
		if ( it != Element::INPUT && it != Element::OUTPUT && it != Element::BRAKE && it != Element::EMPTY )
		{
			return it;
		}
	}
	Log::warning( true, "Chains dont't contain any main element!", Log::CRITICAL, "TChain::getSomeElement()" );
	return *(m_elements.begin());
}

size_t Chain::size() const
{
	return m_elements.size();
}

bool Chain::intersect(const Chain& chain) const
{
	for (auto& it : m_elements)
	{
		if ( it != Element::BRAKE && chain.find( it ) )
			return true;
	}
	return false;
}

const std::set<Element>& Chain::getElements() const
{
	return m_elements;
}

bool NS_CORE operator==( const Chain& chain1, const Chain& chain2 )
{
	return chain1.m_elements == chain2.m_elements;
}

bool NS_CORE operator!=( const Chain& chain1, const Chain& chain2 )
{
	return chain1.m_elements != chain2.m_elements;
}

bool NS_CORE operator<( const Chain& chain1, const Chain& chain2 )
{
	return chain1.m_elements < chain2.m_elements;
}