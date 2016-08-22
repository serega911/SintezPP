#include "Matrix.h"

NS_ARI_USING

Matrix::Matrix( const MatrixTable & table ) :
m_matrix( table )
{
}

Matrix::Matrix( size_t size )
{
	setSize( size );
}

const CellType& Matrix::at( size_t i, size_t j ) const
{
	return m_matrix.at( i ).at( j );
}

CellType& Matrix::at( size_t i, size_t j )
{
	return m_matrix.at( i ).at( j );
}

void Matrix::setSize( size_t size )
{
	m_matrix.resize( size );
	for ( auto& row : m_matrix )
		row.resize( size, 0 );
}

size_t Matrix::getSize() const
{
	return m_matrix.size();
}

const MatrixLine& Matrix::operator[]( size_t i ) const
{
	return m_matrix.at( i );
}

const MatrixTable& Matrix::getMatrix() const
{
	return m_matrix;
}


