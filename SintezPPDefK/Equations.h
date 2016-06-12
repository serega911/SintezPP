#pragma once

#include "../Libraries/GlobalDefines.h"

#include <vector>

#include "Defines.h"
#include "../Libraries/eMainElement.h"

NS_PSS_START

class Equations
{
private:

	static FunctionValue						dfDk( const VariablesSet & set );
	static FunctionValue						dfDw1( const VariablesSet & set );
	static FunctionValue						dfDw2( const VariablesSet & set );
	static FunctionValue						dfDw3( const VariablesSet & set );

public:

	static FunctionValue						wyllys( const VariablesSet & set );

	static FunctionValue						empty( const VariablesSet & set );

	static const Equation						getEquation( const eMainElement & elem );

};

NS_PSS_END