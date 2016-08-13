#pragma once

#include "../Libraries/GlobalDefines.h"
#include "TKinematicScheme.h"
#include <vector>

NS_ARI_START

class TViewer
{
private:
	
	enum eColor
	{
		WHITE = 15
		, RED = 13
		, GREEN = 11
		, BLUE = 9
		, YELLOW = 7
		, ORANGE = 5
		, PURPLE = 3
	};

	static const int							s_colors[];

public:

	static void									printKinematicScheme( const TKinematicScheme& scheme );
	
};

NS_ARI_END