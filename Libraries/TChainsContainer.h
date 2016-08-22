#pragma once

#include <set>
#include <vector>

#include "TGearBox.h"
#include "GlobalDefines.h"

NS_CORE_START

class TChainsContainer
{
private:

	std::set<TChains>							m_container;

public:

	void										add( const TChains& code );
	bool										findIn( const TChains& code ) const;

};

NS_CORE_END
