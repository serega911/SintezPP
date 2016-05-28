#include "Variables.h"
#include "../Libraries/TSingletons.h"

pss::Variables::Variables( size_t size )
{
	resize( size );
}

void pss::Variables::init( const std::vector<TChain>& chains, const TElement& brake, double i )
{
	for ( auto& chain : chains )
	{
		if ( chain.find( pss::TElement::INPUT ) )
		{
			addInputChain( chain );
		}
		else if ( chain.find( brake ) )
		{
			addBrakeChain( chain );
		}
		else if ( chain.find( pss::TElement::OUTPUT ) )
		{
			addOutputChain( chain, i );
		}
		else
		{
			addUndefinedChain( chain );
		}
	}
}

pss::WSet & pss::Variables::operator[]( size_t i )
{
	return m_variables.at( i );
}

void pss::Variables::resize( size_t size )
{
	m_variables.resize( size );
}

void pss::Variables::addInputChain( const TChain& chain )
{
	const auto& elements = chain.getElements();
	for ( auto& elem : elements )
	{
		if ( elem != pss::TElement::INPUT )
		{
			auto gearSetN = elem.getGearSetN() - 1;
			auto elemN = elem.getElemN()._to_integral();
			m_variables[gearSetN][elemN]._def = true;
			m_variables[gearSetN][elemN]._var = &m_wInput;
		}
	}
}

void pss::Variables::addBrakeChain( const TChain& chain )
{
	const auto& elements = chain.getElements();
	for ( auto& elem : elements )
	{
		if ( elem != pss::TElement::BRAKE )
		{
			auto gearSetN = elem.getGearSetN() - 1;
			auto elemN = elem.getElemN()._to_integral();
			m_variables[gearSetN][elemN]._def = true;
			m_variables[gearSetN][elemN]._var = &m_wBrake;
		}
	}
}

void pss::Variables::addOutputChain( const TChain& chain, double i )
{
	m_wOut = 1 / i;
	const auto& elements = chain.getElements();
	for ( auto& elem : elements )
	{
		if ( elem != pss::TElement::OUTPUT )
		{
			auto gearSetN = elem.getGearSetN() - 1;
			auto elemN = elem.getElemN()._to_integral();
			m_variables[gearSetN][elemN]._def = true;
			m_variables[gearSetN][elemN]._var = &m_wOut;
		}
	}
}

void pss::Variables::addUndefinedChain( const TChain& chain )
{
	m_values.push_back( m_wDefaultValue );
	const auto& elements = chain.getElements();
	for ( auto& elem : elements )
	{
		auto gearSetN = elem.getGearSetN() - 1;
		auto elemN = elem.getElemN()._to_integral();
		m_variables[gearSetN][elemN]._def = false;
		m_variables[gearSetN][elemN]._var = &m_values[m_values.size() - 1];
	}
}


