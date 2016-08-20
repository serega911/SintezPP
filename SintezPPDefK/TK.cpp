#include "TK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>
#include <algorithm>

NS_ARI_USING

TK::TK( double dK )
	: core::TK( 0 )
{

	m_dK = dK;

	for ( const auto& range : core::TSingletons::getInstance()->getInitialData()._ranges )
	{
		for ( auto value = range.getBegin(); value <= range.getEnd(); value += m_dK )
		{
			m_kValues.push_back(value);
		}
	}
	m_K.resize( core::TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	m_combi.resize( core::TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	for ( int i = 0; i < m_K.size(); i++ ) // RK: use fill method
	{
		m_combi[i] = 0;
		m_K[i] = m_kValues[0];
	}
}

bool TK::next()
{
	if ( core::next_combination_repetition( m_combi, m_kValues.size() - 1, 0 ) )
	{
		for (int i = 0; i < m_combi.size(); i++)
			m_K[i] = m_kValues[m_combi[i]];
		return true;
	}
	return false;
}

const double TK::operator[]( size_t i ) const
{
	return m_K[i];
}
