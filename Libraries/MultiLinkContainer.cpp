#include "MultiLinkContainer.h"

NS_CORE_USING

void MultiLinkContainer::add( const MultiLinkArray& code )
{
	m_container.insert( code );
}

bool MultiLinkContainer::findIn( const MultiLinkArray& code ) const
{
	if ( m_container.find( code ) != m_container.end() )
	{
		return true;
	}
	return false;
}
