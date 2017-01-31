#pragma once

#include "GlobalDefines.h"
#include <vector>

NS_CORE_START

struct UISpecialData
{
	std::vector<std::pair<float, float>>		_ranges;
	std::vector<float>							_i;
};

NS_CORE_END