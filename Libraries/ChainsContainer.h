#pragma once

#include <set>
#include <vector>

#include "GearBox.h"
#include "GlobalDefines.h"

NS_CORE_START

class ChainsContainer
{
private:

	std::set<ChainArray>							m_container;

public:

	void										add( const ChainArray& code );
	bool										findIn( const ChainArray& code ) const;

};

NS_CORE_END
