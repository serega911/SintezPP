#include "ChainsContainer.h"

NS_CORE_USING

void ChainsContainer::add( const ChainArray& code )
{
	m_container.insert( code );
}

bool ChainsContainer::findIn( const ChainArray& code ) const
{
	if ( m_container.find( code ) != m_container.end() )
	{
		return true;
	}
	return false;
}
