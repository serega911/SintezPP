#include "Variables.h"

const size_t									pss::Variables::s_varSetSize = 4;

pss::Variables::Variables( size_t size )
{
	resize( size );
}

pss::Variables::varSet & pss::Variables::operator[]( size_t i )
{
	return m_variables.at( i );
}

void pss::Variables::resize( size_t size )
{
	m_variables.resize( size );
	for ( auto & it : m_variables )
		it.resize( s_varSetSize );
}
