#pragma once

#include <memory>
#include "../Libraries/GlobalDefines.h"
#include "IFunction.h"

NS_ARI_START

class ISolveFunction;

typedef std::shared_ptr<ISolveFunction> ISolveFunction_p;

class ISolveFunction
{
public:
	virtual double calc( const IFunction_p func, const double intervalBeg, const double intervalEnd ) = 0;
};

NS_ARI_END