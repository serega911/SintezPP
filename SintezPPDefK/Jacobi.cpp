#include "Jacobi.h"
#include "Equations.h"
#include "../Libraries/Log.h"
#include <iostream>

NS_ARI_USING

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
	NS_CORE Log::warning( i >= m_size && j >= m_size, "i,j out of range.", NS_CORE Log::CRITICAL, HERE );
	m_determinant.at( i ).at( j ) = eq;
}

size_t Jacobi::size() const
{
	return m_size;
}

const std::vector<Equation>& Jacobi::operator[]( size_t i ) const
{
	return m_determinant.at( i );
}
