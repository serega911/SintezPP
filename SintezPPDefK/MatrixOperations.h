#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Matrix.h"


NS_PSS_START

class MatrixOperations
{
public:

	static CellType								calcDeterminant( const Matrix& matrix );
	static Matrix								convertToInversMatrix( const Matrix& matrix );

};


NS_PSS_END