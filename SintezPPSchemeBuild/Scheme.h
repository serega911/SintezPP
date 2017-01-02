#pragma once

#include <vector>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Code.h"
#include "../Libraries/Chain.h"
#include "../Libraries/Link.h"

NS_ARI_START

class Scheme
{
private:

	struct Link
	{
		NS_CORE Link	_link;
		NS_CORE Chain	_chains;
	};

	std::vector<Link>							m_links;

public:
	Scheme(const NS_CORE Code& code);
};



NS_ARI_END