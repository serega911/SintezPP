#include "Jacobi.h"
#include "Equations.h"
#include <iostream>

NS_PSS_USING

Jacobi::Jacobi() : m_size( 0 )
{
}

void Jacobi::setSize( size_t size )
{
	m_size = size;
	m_determinant.resize( m_size );
	for ( auto & it : m_determinant )
	{
		it.resize( m_size );
		for ( auto & eq : it )
		{
			eq = Equations::empty;
		}
	}
		
}

void Jacobi::setEquation( size_t i, size_t j, const Equation & eq )
{
	if ( i >= m_size && j >= m_size )
		std::cout << "i,j out of range. Determinant.cpp\n";
	m_determinant.at( i ).at( j ) = eq;
}

size_t pss::Jacobi::size() const
{
	return m_size;
}

const std::vector<Equation>& Jacobi::operator[]( size_t i ) const
{
	return m_determinant.at( i );
}
