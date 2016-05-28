#include "../Libraries/TChain.h"

void pss::TChain::addLinkToChain(const pss::TLink & link)
{
	m_elements.insert(link.getElem1());
	m_elements.insert(link.getElem2());
}

void pss::TChain::addElementToChain(const TElement & elem)
{
	m_elements.insert(elem);
}

void pss::TChain::addChainToChain(const TChain & chain)
{
	for (auto& it : chain.m_elements)
		m_elements.insert(it);
}

void pss::TChain::clear()
{
	m_elements.clear();
}

bool pss::TChain::find(const TElement & element) const
{
	if (m_elements.find(element) != m_elements.end())
		return true;
	else
		return false;
}

bool pss::TChain::checkElemByOnePlanetarySet() const
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

const pss::TElement& pss::TChain::getFirst() const
{
	return *(m_elements.begin());
}

int pss::TChain::size() const
{
	return m_elements.size();
}

bool pss::TChain::intersect(const TChain& chain)
{
	for (auto& it : m_elements)
	{
		if (chain.find(it))
			return true;
	}
	return false;
}

const std::set<pss::TElement>& pss::TChain::getElements() const
{
	return m_elements;
}

bool pss::operator<( const TChain& chain1, const TChain& chain2 )
{
	return chain1.m_elements < chain2.m_elements;
}
