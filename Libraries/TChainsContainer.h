#pragma once

#include <set>
#include <vector>

#include "TGearBox.h"
#include "GlobalDefines.h"

NS_CORE_START

class TChainsContainer
{
private:

	std::set<TChainArray>							m_container;

public:

	void										add( const TChainArray& code );
	bool										findIn( const TChainArray& code ) const;

};

NS_CORE_END
