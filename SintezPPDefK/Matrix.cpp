#include "Matrix.h"

NS_PSS_USING

pss::Matrix::Matrix( const MatrixTable & table ) :
m_matrix( table )
{
}

pss::Matrix::Matrix( size_t size )
{
	setSize( size );
}

const CellType& pss::Matrix::at( size_t i, size_t j ) const
{
	return m_matrix.at( i ).at( j );
}

CellType& pss::Matrix::at( size_t i, size_t j )
{
	return m_matrix.at( i ).at( j );
}

void pss::Matrix::setSize( size_t size )
{
	m_matrix.resize( size );
	for ( auto& row : m_matrix )
		row.resize( size, 0 );
}

size_t pss::Matrix::getSize() const
{
	return m_matrix.size();
}

const MatrixLine& pss::Matrix::operator[]( size_t i ) const
{
	return m_matrix.at( i );
}

const MatrixTable& pss::Matrix::getMatrix() const
{
	return m_matrix;
}


