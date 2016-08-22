#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Matrix.h"


NS_ARI_START

class MatrixOperations
{
public:

	static MatrixLine							solveGaus( const Matrix& systemMatrix, const MatrixLine& rightParts );
	static MatrixLine							solveKramer( const Matrix& systemMatrix, const MatrixLine& rightParts );

	static CellType								determinant( const Matrix& matrix );
	static Matrix								inverse( const Matrix& matrix );
	static Matrix								minor( const Matrix& matrix, int i, int j );

	static MatrixLine							multiple( const Matrix& matrix, const MatrixLine& vector );
	static Matrix								multiple( const Matrix& matrix1, const Matrix& matrix2 );
	static MatrixLine							delta( const MatrixLine& vector1, const MatrixLine& vector2 );



};


NS_ARI_END