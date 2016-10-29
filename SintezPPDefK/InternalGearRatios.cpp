#include "InternalGearRatios.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/Singletons.h"
#include <iostream>
#include <algorithm>

NS_ARI_USING

InternalGearRatios::InternalGearRatios( NS_CORE InternalGearRatioValue dK )
	: core::InternalGearRatios( 0 )
{
	m_dK = dK;
	m_currentOrderedSample = 0;

	for ( const auto& range : core::Singletons::getInstance()->getInitialData()._ranges )
	{
		for ( NS_CORE InternalGearRatioValue value = range.getBegin(); value <= range.getEnd(); value = m_dK + value )
		{
			m_kValues.push_back(value);
		}
	}
	m_K.resize( core::Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears, m_kValues[0] );
	m_combi.resize( core::Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears, 0 );
}

ari::InternalGearRatios::InternalGearRatios( NS_CORE InternalGearRatios& k )
	: core::InternalGearRatios( k )
{
}

bool InternalGearRatios::next()
{
	m_currentOrderedSample++;
	if ( NS_CORE Singletons::getInstance()->getCombinatorics()->getOrderedSample( m_kValues.size(), m_combi.size(), m_currentOrderedSample, m_combi ) )
	{
		for ( size_t i = 0; i < m_combi.size(); i++ )
			m_K[i] = m_kValues[m_combi[i]];
		return true;
	}
	return false;
}

const NS_CORE InternalGearRatioValue InternalGearRatios::operator[]( size_t i ) const
{
	return m_K[i];
}
