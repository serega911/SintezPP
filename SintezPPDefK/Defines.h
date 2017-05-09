#pragma once

#include <functional>
#include <vector>

#include "VariablesSet_fwd.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

typedef float VariableValue;
typedef float FunctionValue;
typedef std::function<FunctionValue( const VariablesSet & )> Equation;

typedef float								CellType;
typedef std::vector<CellType>				MatrixLine;
typedef std::vector<MatrixLine>				MatrixTable;

NS_ARI_END