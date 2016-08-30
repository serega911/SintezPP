#include "TChainsContainer.h"

NS_CORE_USING

void TChainsContainer::add( const TChainArray& code )
{
	m_container.insert(code);
}

bool TChainsContainer::findIn( const TChainArray& code ) const
{
	if (m_container.find(code) != m_container.end())
	{
		return true;
	}	
	return false;
}
