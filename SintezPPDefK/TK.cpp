#include "TK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>
#include <algorithm>

NS_ARI_USING

TK::TK( NS_CORE TKValue dK )
	: core::TK( 0 )
{
	m_dK = dK;
	m_currentOrderedSample = 0;

	for ( const auto& range : core::TSingletons::getInstance()->getInitialData()._ranges )
	{
		for ( NS_CORE TKValue value = range.getBegin(); value <= range.getEnd(); value = m_dK + value )
		{
			m_kValues.push_back(value);
		}
	}
	m_K.resize( core::TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears, m_kValues[0] );
	m_combi.resize( core::TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears, 0 );
}

ari::TK::TK( NS_CORE TK& k )
	: core::TK( k )
{
}

bool TK::next()
{
	m_currentOrderedSample++;
	if ( NS_CORE TSingletons::getInstance()->getCombinatorics()->getOrderedSample( m_kValues.size(), m_combi.size(), m_currentOrderedSample, m_combi ) )
	{
		for ( size_t i = 0; i < m_combi.size(); i++ )
			m_K[i] = m_kValues[m_combi[i]];
		return true;
	}
	return false;
}

const NS_CORE TKValue TK::operator[]( size_t i ) const
{
	return m_K[i];
}
