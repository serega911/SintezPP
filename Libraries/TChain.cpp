#include "../Libraries/TChain.h"
#include <algorithm>

core::TChain::TChain( const TElement& element )
{
	addElementToChain( element );
}

NS_CORE_USING

TChain::TChain()
{
}

void TChain::addLinkToChain(const TLink & link)
{
	m_elements.insert(link.getElem1());
	m_elements.insert(link.getElem2());
}

void TChain::addElementToChain(const TElement & elem)
{
	m_elements.insert(elem);
}

void TChain::addChainToChain(const TChain & chain)
{
	for (auto& it : chain.m_elements)
		m_elements.insert(it);
}

void TChain::clear()
{
	m_elements.clear();
}

bool TChain::find(const TElement & element) const
{
	if ( m_elements.find( element ) != m_elements.end() )
		return true;
	else
		return false;
}

bool TChain::checkElemByOnePlanetarySet() const
{
	for (int i = 1; i <= 3; i++)
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

const TElement& TChain::getSomeElement() const
{
	for ( const auto& it : m_elements )
	{
		if ( it != TElement::INPUT && it != TElement::OUTPUT && it != TElement::BRAKE && it != TElement::EMPTY )
		{
			return it;
		}
	}
	TLog::warning( true, "Chains dont't contain any main element!", TLog::CRITICAL, "TChain::getSomeElement()" );
	return *(m_elements.begin());
}

size_t TChain::size() const
{
	return m_elements.size();
}

bool TChain::intersect(const TChain& chain) const
{
	for (auto& it : m_elements)
	{
		if ( it != TElement::BRAKE && chain.find( it ) )
			return true;
	}
	return false;
}

const std::set<TElement>& TChain::getElements() const
{
	return m_elements;
}

bool NS_CORE operator==( const TChain& chain1, const TChain& chain2 )
{
	return chain1.m_elements == chain2.m_elements;
}

bool NS_CORE operator!=( const TChain& chain1, const TChain& chain2 )
{
	return chain1.m_elements != chain2.m_elements;
}

bool NS_CORE operator<( const TChain& chain1, const TChain& chain2 )
{
	return chain1.m_elements < chain2.m_elements;
}