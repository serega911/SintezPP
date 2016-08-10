#pragma once

#include <vector>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TChain.h"

NS_ARI_START

class TKinematicScheme
{
private:

	typedef std::vector<std::vector<NS_CORE TChain> > Map;

	Map											m_map;

	void										init();

public:
};

NS_ARI_END