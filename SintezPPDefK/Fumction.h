#pragma once

#include <functional>

namespace pss
{
	typedef double variable;
	typedef double value;
	typedef std::function<value( variable, variable, variable, variable )> equation;
}