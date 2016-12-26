#pragma once

#include <vector>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Code.h"
#include "../Libraries/Link.h"

NS_ARI_START

class Scheme
{
private:

	NS_CORE ChainArray							m_chains;

public:
	Scheme(const NS_CORE Code& code);
};



NS_ARI_END