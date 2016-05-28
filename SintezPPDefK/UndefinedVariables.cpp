#include "UndefinedVariables.h"

#include "../Libraries/TSingletons.h"

void pss::UndefinedVariables::addK()
{

}

pss::UndefinedVariables::UndefinedVariables( std::vector<Variables> & vectVar )
{
	auto N = pss::TSingletons::getInstance( )->getNumberOfPlanetaryGears( );
	for ( size_t i = 0; i < N; i++ )
	{
		m_kValues.push_back( m_kDefaultValue );
		for ( auto& var : vectVar )
		{
			var[i][0]._def = false;
			var[i][0]._var = &m_kValues[m_kValues.size( ) - 1];
		}
		m_variables.push_back( &m_kValues[m_kValues.size( ) - 1] );
	}

	for ( auto& var : vectVar )
	{
		for ( auto & v : var.m_values )
		{
			m_variables.push_back(&v);
		}
	}

}

pss::variable& pss::UndefinedVariables::operator[]( size_t i )
{
	return *m_variables.at( i );
}
