#pragma once

#include <memory>
#include "../Libraries/GlobalDefines.h"
#include "ISolveFunction.h"

NS_ARI_START

class SolveFunctionDiv;

typedef std::shared_ptr<SolveFunctionDiv> SolveFunctionDiv_p;

class SolveFunctionDiv: public ISolveFunction
{
public:

	static SolveFunctionDiv_p					create();

	virtual double calc( const IFunction_p func, const double intervalBeg, const double intervalEnd ) override;
};

NS_ARI_END