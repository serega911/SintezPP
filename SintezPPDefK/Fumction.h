#pragma once

#include <functional>
#include "VariablesSet_fwd.h"

namespace pss
{
	typedef double VariableValue;
	typedef double FunctionValue;
	typedef std::function<FunctionValue( const VariablesSet & )> Equation;
}