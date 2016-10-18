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

	NS_CORE TKArray								calculate( const NS_CORE TCode& code );
	static NS_CORE TI							podModul( const NS_CORE TCode & code, const NS_ARI TK &k );
	static size_t								countOfDifferent( const NS_CORE TI& i);

};

NS_ARI_END