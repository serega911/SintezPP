#pragma once

#include <memory>
#include "../Libraries/GlobalDefines.h"

NS_ARI_START
class IFunction;

typedef std::shared_ptr<IFunction> IFunction_p;

class IFunction
{
public:
	virtual double calc( double ) const = 0;
};

NS_ARI_END