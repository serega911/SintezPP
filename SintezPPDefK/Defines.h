#pragma once

#include <functional>
#include <vector>

#include "VariablesSet_fwd.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

typedef double VariableValue;
typedef double FunctionValue;
typedef std::function<FunctionValue( const VariablesSet & )> Equation;

typedef double								CellType;
typedef std::vector<CellType>				MatrixLine;
typedef std::vector<MatrixLine>				MatrixTable;

NS_ARI_END