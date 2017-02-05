#pragma once

#include "GlobalDefines.h"
#include <vector>
#include <memory>

NS_CORE_START

struct UISpecialData;

typedef std::shared_ptr<UISpecialData> UISpecialData_p;

struct UISpecialData
{
	std::vector<std::pair<float, float>>		_ranges;
	std::vector<float>							_i;

	static UISpecialData_p create(){ return UISpecialData_p( new UISpecialData ); };
};

NS_CORE_END