#pragma once

#include <set>
#include <vector>

#include "GearBox.h"
#include "GlobalDefines.h"

NS_CORE_START

class MultiLinkContainer
{
private:

	std::set<MultiLinkArray>							m_container;

public:

	void										add( const MultiLinkArray& code );
	bool										findIn( const MultiLinkArray& code ) const;

};

NS_CORE_END
