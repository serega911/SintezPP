#include "MultiLink.h"
#include "Singletons.h"
#include <algorithm>

core::MultiLink::MultiLink( const Element& element )
{
	addElementToChain( element );
}

NS_CORE_USING

MultiLink::MultiLink()
{
}

void MultiLink::addLinkToChain( const Link & link )
{
	const auto& elem1 = link.getElem1();
	const auto& elem2 = link.getElem2();

	const bool condition = m_elements.size() != 0 && !( find( elem1 ) || find( elem2 ) );
	Log::warning( condition, "Chains dont't contain one ofelements!", Log::CRITICAL, "TChain::addLinkToChain()" );

	m_elements.insert( elem1 );
	m_elements.insert( elem2 );
}

void MultiLink::addElementToChain( const Element & elem )
{
	const bool condition = m_elements.size() != 0;
	Log::warning( condition, "Chains is not mpty!", Log::CRITICAL, "TChain::addElementToChain()" );

	m_elements.insert( elem );
}

void MultiLink::addChainToChain( const MultiLink & chain )
{
	const bool condition = !intersect( chain );
	Log::warning( condition, "Chains dont't contain one ofelements!", Log::CRITICAL, "TChain::addChainToChain()" );

	for ( auto& it : chain.m_elements )
		m_elements.insert( it );
}

void MultiLink::clear()
{
	m_elements.clear();
}

bool MultiLink::find( const Element & element ) const
{
	return m_elements.find( element ) != m_elements.end();
}

bool MultiLink::checkElemByOnePlanetarySet() const
{
	const GearSetNumber N( Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	for ( GearSetNumber i( 1 ); i <= N; ++i )
	{
		int count = 0;
		for ( auto &it : m_elements )
		{
			if ( it.getGearSetN() == i )
				count++;
		}
		if ( count > 1 )
		{
			return false;
		}
	}
	return true;
}

bool core::MultiLink::checkIsChainCorrect() const
{
	if ( find( NS_CORE Element::INPUT ) && find( NS_CORE Element::BRAKE ) )
		return false;
	else if ( find( NS_CORE Element::BRAKE ) && find( NS_CORE Element::OUTPUT ) )
		return false;

	return true;
}

const Element& MultiLink::getSomeElement() const
{
	for ( const auto& it : m_elements )
	{
		if ( it != Element::INPUT && it != Element::OUTPUT && it != Element::BRAKE && it != Element::EMPTY )
		{
			return it;
		}
	}
	Log::warning( true, "Chains dont't contain any main element!", Log::CRITICAL, "TChain::getSomeElement()" );
	return *( m_elements.begin() );
}

size_t MultiLink::size() const
{
	return m_elements.size();
}

bool MultiLink::intersect( const MultiLink& chain ) const
{
	for ( auto& it : m_elements )
	{
		if ( it != Element::BRAKE && chain.find( it ) )
			return true;
	}
	return false;
}

const std::set<Element>& MultiLink::getElements() const
{
	return m_elements;
}

bool core::MultiLink::loadFromFile( std::istream& )
{
	NS_CORE Log::warning( true, "NOT IMPLEMENTED", NS_CORE Log::CRITICAL, HERE );
	return false;
}

void core::MultiLink::writeToFile( std::ostream& file) const
{
	for ( const auto & elem : m_elements )
	{
		elem.writeTofile( file );
	}
}

bool NS_CORE operator==( const MultiLink& chain1, const MultiLink& chain2 )
{
	return chain1.m_elements == chain2.m_elements;
}

bool NS_CORE operator!=( const MultiLink& chain1, const MultiLink& chain2 )
{
	return chain1.m_elements != chain2.m_elements;
}

bool NS_CORE operator<( const MultiLink& chain1, const MultiLink& chain2 )
{
	return chain1.m_elements < chain2.m_elements;
}