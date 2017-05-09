#pragma once

#include <map>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Element.h"

NS_ARI_START

struct KpdValue
{
	float _kpdA;
	float _kpdB;
};

typedef std::map<NS_CORE Element, int>		Z;
typedef std::map<NS_CORE Element, float>	M;
typedef std::map<NS_CORE Element, float>	W;
typedef std::map<NS_CORE Element, char>		N;
typedef std::map<NS_CORE GearSetNumber, KpdValue> KpdZac;

NS_ARI_END