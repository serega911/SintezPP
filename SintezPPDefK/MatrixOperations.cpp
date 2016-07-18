
#include "MatrixOperations.h"

NS_PSS_USING

pss::CellType pss::MatrixOperations::determinant( const Matrix& matrix )
{
	auto size = matrix.getSize();
	if ( size == 1 ) return matrix[0][0];
	else
	{
		double res = 0;
		for ( int i = 0; i < size; i++ )
		{
			res += matrix[i][0] * ( determinant( minor( matrix, i, 0 )  ) )	*( i % 2 == 0 ? -1.0 : 1.0 );
		}
		return res;
	}
}

MatrixLine operator*( const MatrixLine & line, const double & k )
{
	MatrixLine ret = line;
	for ( auto& cell : ret )
	{
		cell *= k;
	}
	return ret;
}

MatrixLine operator-( const MatrixLine & line1, const MatrixLine & line2 )
{
	auto ret = line1;
	for ( auto i = 0; i < line2.size( ); i++ )
	{
		ret[i] -= line2[i];
	}

	return ret;
}

pss::MatrixLine pss::MatrixOperations::solveGaus( const Matrix& systemMatrix, const MatrixLine& rightParts )
{

	auto system = systemMatrix.getMatrix();
	auto right = rightParts;

	const int n = system.size( );

	for ( int i = 0; i < n; ++i ) 
	{
		int k = i;

		for ( int j = i + 1; j < n; ++j )
		{
			if ( abs( system[j][i] ) > abs( system[k][i] ) )
			{
				k = j;
			}
		}
			
		if ( k != i )
		{
			std::swap( system[i], system[k] );
			std::swap( right[i], right[k] );
		}

		if ( system[i][i] != 0 )
		{
			for ( int j = i + 1; j < n; ++j )
			{
				system[i][j] /= system[i][i];
			}
			right[i] /= system[i][i];
		}
		else
		{
			right.clear( );
			return right;
		}
			
		for ( int j = 0; j < n; ++j )
		{
			if ( j != i )
			{
				for ( int k = i + 1; k < n; ++k )
				{
					system[j][k] -= system[i][k] * system[j][i];
				}
				right[j] -= right[i] * system[j][i];
			}
		}
	}

	return right;
}

Matrix pss::MatrixOperations::minor( const Matrix& matrix, int i, int j )
{
	const auto size = matrix.getSize();
	if ( i < size && j < size && i >= 0 && j >= 0 )
	{
		if ( size > 1 )
		{
			MatrixTable res( size - 1 );
			for ( auto i = 0; i < size - 1; i++ )
			{
				res[i].resize( size - 1, 0 );
			}

			for ( int i1 = 0; i1 < size; i1++ )
			{

				for ( int j1 = 0; j1 < size; j1++ )
				{
					if ( i1 != i && j1 != j )
					{
						int it = ( i1 > i ) ? -1 : 0;
						int jt = ( j1 > j ) ? -1 : 0;
						res[i1 + it][j1 + jt] = matrix[i1][j1];
					}
				}
			}
			return Matrix( res );
		}
	}
}

Matrix pss::MatrixOperations::inverse( const Matrix& matrix )
{
	const auto size = matrix.getSize();
	MatrixTable ret( size );
	for ( auto i = 0; i < size; i++ )
	{
		ret[i].resize( size, 0 );
	}

	double d = determinant( matrix );
	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
		{
			ret[i][j] = determinant( minor( matrix, j, i ) ) / d*( ( i + j ) % 2 == 0 ? -1.0 : 1.0 );
		}
	}
	return Matrix( ret );
}

MatrixLine pss::MatrixOperations::multiple( const Matrix& matrix, const MatrixLine& vector )
{
	const auto size = matrix.getSize();
	if ( vector.size() == size )
	{
		MatrixLine ret( size );
		for ( int i = 0; i < size; i++ )
		{
			double val = 0;
			for ( int j = 0; j < size; j++ )
			{
				val += matrix[i][j] * vector[j];
			}
			ret[i] = val;
		}
		return ret;
	}
	return MatrixLine( 0 );
}

Matrix pss::MatrixOperations::multiple( const Matrix& matrix1, const Matrix& matrix2 )
{
	const auto size = matrix1.getSize();
	if ( size == matrix2.getSize() )
	{
		MatrixTable res( size );
		for ( auto i = 0; i < size; i++ )
		{
			res[i].resize( size, 0 );
		}

		for ( int i = 0; i < size; i++ )
		{
			for ( int j = 0; j < size; j++ )
			{
				double val = 0;
				for ( int k = 0; k < size; k++ )
				{
					val += matrix1[k][i] * matrix2[j][k];
				}
				res[j][i] = val;
			}
		}
		return Matrix( res );
	}
	return Matrix( 0 );
}

pss::MatrixLine pss::MatrixOperations::delta( const MatrixLine& vector1, const MatrixLine& vector2 )
{
	const auto size = vector1.size();
	MatrixLine ret( size );

	for ( auto i = 0; i < size; i++ )
	{
		ret[i] = vector1[i] - vector2[i];
	}

	return ret;
}