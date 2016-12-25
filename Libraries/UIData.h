#pragma once

#include <vector>

#include "Log.h"
#include "GlobalDefines.h"


NS_CORE_START

struct UIAppData
{
	int _w;
	int _n;
	int _d;
};

struct UIGenerateData : public UIAppData
{

};

struct UIKefKData : public UIAppData
{
private:
	std::vector<double> _i;
	std::vector<std::pair<double, double>> _ranges;
};


NS_CORE_END