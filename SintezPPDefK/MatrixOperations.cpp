
#include "MatrixOperations.h"

NS_ARI_USING

CellType MatrixOperations::determinant( const Matrix& matrix )
{
	auto size = matrix.getSize();
	if ( size == 1 ) return matrix[0][0];
	else
	{
		double res = 0;
		for ( size_t i = 0; i < size; i++ )
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
	for ( size_t i = 0; i < line2.size(); i++ )
	{
		ret[i] -= line2[i];
	}

	return ret;
}

MatrixLine operator+( const MatrixLine & line1, const MatrixLine & line2 )
{
	auto ret = line1;
	for ( size_t i = 0; i < line2.size(); i++ )
	{
		ret[i] += line2[i];
	}

	return ret;
}

Matrix createSpecMatrix( const Matrix& native, const MatrixLine& right, const int pos )
{
	Matrix ret = native;
	for ( size_t i = 0; i < ret.getSize(); i++ )
	{
		ret.at( i, pos ) = right[i];
	}
	return ret;
}

MatrixLine MatrixOperations::solveGaus( const Matrix& systemMatrix, const MatrixLine& rightParts )
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

		if ( abs(system[i][i]) > 0.0001 )
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

ari::MatrixLine ari::MatrixOperations::solveKramer( const Matrix& systemMatrix, const MatrixLine& rightParts )
{
	MatrixLine ans( systemMatrix.getSize() );

	auto det = determinant( systemMatrix );
	if ( abs( det ) > 0.001 )
	{
		for ( size_t i = 0; i < systemMatrix.getSize(); i++ )
		{
			auto currDet = determinant( createSpecMatrix( systemMatrix, rightParts, i ) );
			ans[i] = currDet / det;
		}
	}
	else
	{
		ans.clear();
	}

	return ans;
}

Matrix MatrixOperations::minor( const Matrix& matrix, size_t i, size_t j )
{
	const auto size = matrix.getSize();
	if ( i < size && j < size && i >= 0 && j >= 0 )
	{
		if ( size > 1 )
		{
			MatrixTable res( size - 1 );
			for ( size_t i1 = 0; i1 < size - 1; i1++ )
			{
				res[i1].resize( size - 1, 0 );
			}

			for ( size_t i1 = 0; i1 < size; i1++ )
			{

				for ( size_t j1 = 0; j1 < size; j1++ )
				{
					if ( i1 != i && j1 != j )
					{
						size_t it = ( i1 > i ) ? -1 : 0;
						size_t jt = ( j1 > j ) ? -1 : 0;
						res[i1 + it][j1 + jt] = matrix[i1][j1];
					}
				}
			}
			return Matrix( res );
		}
	}
}

Matrix MatrixOperations::inverse( const Matrix& matrix )
{
	const auto size = matrix.getSize();
	MatrixTable ret( size );
	for ( size_t i = 0; i < size; i++ )
	{
		ret[i].resize( size, 0 );
	}

	double d = determinant( matrix );
	for ( size_t i = 0; i < size; i++ )
	{
		for ( size_t j = 0; j < size; j++ )
		{
			ret[i][j] = determinant( minor( matrix, j, i ) ) / d*( ( i + j ) % 2 == 0 ? -1.0 : 1.0 );
		}
	}
	return Matrix( ret );
}

MatrixLine MatrixOperations::multiple( const Matrix& matrix, const MatrixLine& vector )
{
	const auto size = matrix.getSize();
	if ( vector.size() == size )
	{
		MatrixLine ret( size );
		for ( size_t i = 0; i < size; i++ )
		{
			double val = 0;
			for ( size_t j = 0; j < size; j++ )
			{
				val += matrix[i][j] * vector[j];
			}
			ret[i] = val;
		}
		return ret;
	}
	return MatrixLine( 0 );
}

Matrix MatrixOperations::multiple( const Matrix& matrix1, const Matrix& matrix2 )
{
	const auto size = matrix1.getSize();
	if ( size == matrix2.getSize() )
	{
		MatrixTable res( size );
		for ( size_t i = 0; i < size; i++ )
		{
			res[i].resize( size, 0 );
		}

		for ( size_t i = 0; i < size; i++ )
		{
			for ( size_t j = 0; j < size; j++ )
			{
				double val = 0;
				for ( size_t k = 0; k < size; k++ )
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

MatrixLine MatrixOperations::delta( const MatrixLine& vector1, const MatrixLine& vector2 )
{
	const auto size = vector1.size();
	MatrixLine ret( size );

	for ( size_t i = 0; i < size; i++ )
	{
		ret[i] = vector1[i] - vector2[i];
	}

	return ret;
}
