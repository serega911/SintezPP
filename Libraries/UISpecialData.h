#pragma once

#include "GlobalDefines.h"
#include <vector>
#include <memory>

NS_CORE_START

struct UISpecialData;

typedef std::shared_ptr<UISpecialData> UISpecialData_p;

struct UISpecialData
{
	std::vector<std::pair<double, double>>		_ranges;
	std::vector<double>							_i;

	static UISpecialData_p create(){ return UISpecialData_p( new UISpecialData ); };
};

NS_CORE_END