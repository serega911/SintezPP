#pragma once

#include "../Libraries/GlobalDefines.h"

#include <vector>

#include "Defines.h"
#include "../Libraries/eMainElement.h"

NS_ARI_START

class Equations
{
private:

	static bool									s_statusOK;

	static FunctionValue						dfDk( const VariablesSet & set );
	static FunctionValue						dfDw1( const VariablesSet & set );
	static FunctionValue						dfDw2( const VariablesSet & set );
	static FunctionValue						dfDw3( const VariablesSet & set );

	static void									setStatusFail();
	static void									processBadCondition( const bool condition, const std::string & message = "" );

public:

	static FunctionValue						wyllys( const VariablesSet & set );

	static FunctionValue						empty( const VariablesSet & set );

	static FunctionValue						calcWSun( const VariablesSet & set );
	static FunctionValue						calcWEpicyclic( const VariablesSet & set );
	static FunctionValue						calcWCarrirer( const VariablesSet & set );
	static FunctionValue						calcKValue( const VariablesSet & set );
	static bool									check( const VariablesSet & set );
	static FunctionValue						calcOne( const NS_CORE eMainElement elem, const VariablesSet & set );

	static const Equation						getEquation( const NS_CORE eMainElement & elem );

	static bool									getStatusOK();
	static void									resetStatusOK();

};

NS_ARI_END