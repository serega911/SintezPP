#pragma once

#include <vector>

#include "TK.h"
#include "../Libraries/TKArray.h"
#include "../Libraries/TIArray.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TI.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class DefKSelection
{
public:

	std::pair<NS_CORE TKArray, NS_CORE TIArray>	calculate( const NS_CORE TCode& code );
	static NS_CORE TI							podModul( const NS_CORE TCode & code, const NS_ARI TK &k );


};

NS_ARI_END