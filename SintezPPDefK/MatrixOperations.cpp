
#include "MatrixOperations.h"

NS_PSS_USING

pss::CellType pss::MatrixOperations::calcDeterminant( const Matrix& matrix )
{
	int i, j;
	CellType det = 0;

	auto size = matrix.getSize();

	if ( size == 1 )
	{
		det = matrix.at( 0, 0 );
	}
	else if ( size == 2 )
	{
		det = matrix.at( 0, 0 ) * matrix.at( 1, 1 ) - matrix.at( 0, 1 ) * matrix.at( 1, 0 );
	}
	else
	{
		MatrixTable matr;
		matr.resize( size - 1 );
		for ( i = 0; i < size; ++i )
		{
			for ( j = 0; j < size - 1; ++j )
			{
				if ( j < i )
					matr[j] = matrix[j];
				else
					matr[j] = matrix[j + 1];
			}
			det += pow( -1.0, ( i + j ) ) * calcDeterminant( Matrix(matr) ) * matrix.at(i, size - 1);
		}
	}
	return det;
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

Matrix pss::MatrixOperations::convertToInversMatrix( const Matrix& matrix )
{
	auto size = matrix.getSize();
	
	MatrixTable tmp = matrix.getMatrix( );
	MatrixTable ret( size );
	for ( auto i = 0; i < size; i++ )
	{
		ret[i].resize( size, 0 );
		ret[i][i] = 1;
	}
	
	for ( auto i = 0; i < size; i++ )
	{
		if ( tmp[i][i] == 0 )
		{
			//exception
		}
		else
		{
			for ( auto line = i + 1; line < size; line++ )
			{
				auto k = tmp[line][i] / tmp[i][i];
				tmp[line] = tmp[line] - tmp[i] * k;
				ret[line] = ret[line] - ret[i] * k;
			}
		}

	}

	for ( int i = size-1; i >= 1; i-- )
	{
		if ( tmp[i][i] == 0 )
		{
			//exception
		}
		else
		{
			for ( int line = i - 1; line >= 0; line-- )
			{
				auto k = tmp[line][i] / tmp[i][i];
				tmp[line] = tmp[line] - tmp[i] * k;
				ret[line] = ret[line] - ret[i] * k;
			}
		}

	}

	for ( auto i = 0; i < size; i++ )
	{
		tmp[i] = tmp[i] * ( 1 / tmp[i][i] );
		ret[i] = ret[i] * ( 1 / ret[i][i] );
	}
	
	return Matrix(ret);
}

