#pragma once

#include "../Libraries/GlobalDefines.h"
#include "KinematicScheme.h"
#include <vector>

NS_ARI_START

class Viewer
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

	static void									printKinematicScheme( const KinematicScheme& scheme );
	
};

NS_ARI_END