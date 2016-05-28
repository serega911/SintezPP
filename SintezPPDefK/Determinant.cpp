#include "Determinant.h"
#include "Equations.h"
#include <iostream>

pss::Determinant::Determinant() : m_size( 0 )
{
}

void pss::Determinant::setSize( size_t size )
{
	m_size = size;
	m_determinant.resize( m_size );
	for ( auto & it : m_determinant )
	{
		it.resize( m_size );
		for ( auto & eq : it )
		{
			eq = Equations::s_equations[1];
		}
	}
		
}

void pss::Determinant::setEquation( size_t i, size_t j, equation eq )
{
	if ( i >= m_size && j >= m_size )
		std::cout << "i,j out of range. Determinant.cpp\n";
	m_determinant.at( i ).at( j ) = eq;
}

const std::vector<pss::equation>& pss::Determinant::operator[]( size_t i )
{
	return m_determinant.at( i );
}
