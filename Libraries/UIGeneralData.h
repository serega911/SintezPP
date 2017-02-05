#pragma once

#include "GlobalDefines.h"
#include <memory>

NS_CORE_START

struct UIGeneralData;

typedef std::shared_ptr<UIGeneralData> UIGeneralData_p;

struct UIGeneralData
{
	size_t										_w;
	size_t										_n;
	size_t										_d;

	static UIGeneralData_p create(){ return UIGeneralData_p( new UIGeneralData ); };

};

NS_CORE_END