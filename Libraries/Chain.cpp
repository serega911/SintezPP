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
	const auto& elem1 = link.getElem1();
	const auto& elem2 = link.getElem2();

	const bool condition = m_elements.size() != 0 && !( find( elem1 ) || find( elem2 ) );
	Log::warning( condition, "Chains dont't contain one ofelements!", Log::CRITICAL, "TChain::addLinkToChain()" );

	m_elements.insert( elem1 );
	m_elements.insert( elem2 );
}

void Chain::addElementToChain(const Element & elem)
{
	const bool condition = m_elements.size() != 0;
	Log::warning( condition, "Chains is not mpty!", Log::CRITICAL, "TChain::addElementToChain()" );

	m_elements.insert(elem);
}

void Chain::addChainToChain(const Chain & chain)
{
	const bool condition = !intersect( chain );
	Log::warning( condition, "Chains dont't contain one ofelements!", Log::CRITICAL, "TChain::addChainToChain()" );

	for (auto& it : chain.m_elements)
		m_elements.insert(it);
}

void Chain::clear()
{
	m_elements.clear();
}

bool Chain::find(const Element & element) const
{
	return m_elements.find( element ) != m_elements.end();
}

bool Chain::checkElemByOnePlanetarySet() const
{
	const GearSetNumber N (Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears);
	for ( GearSetNumber i(1); i <= N; i++ )
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

bool core::Chain::checkIsChainCorrect() const
{
	if ( find( NS_CORE Element::INPUT ) && find( NS_CORE Element::BRAKE ) )
		return false;
	else if ( find( NS_CORE Element::BRAKE ) && find( NS_CORE Element::OUTPUT ) )
		return false;

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