#include "InternalGearRatios.h"
#include "../Libraries/Singletons.h"
#include <iostream>
#include <algorithm>

NS_ARI_USING

InternalGearRatios::InternalGearRatios( const NS_CORE InternalGearRatioValue dK )
: core::InternalGearRatios(0)
{
	NS_CORE InternalGearRatioValueArray kValues;

	for ( const auto& range : core::Singletons::getInstance()->getInitialData()._ranges )
	{
		const auto end = range.getEnd();
		for ( NS_CORE InternalGearRatioValue value = range.getBegin(); value <= end; value = dK + value )
		{
			kValues.push_back( value );
		}
	}

	m_combi.init( kValues, core::Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	m_K = m_combi.get();

}

ari::InternalGearRatios::InternalGearRatios( const NS_CORE InternalGearRatioValueArray& k )
	: core::InternalGearRatios( k )
{

}

ari::InternalGearRatios::InternalGearRatios( NS_CORE InternalGearRatios& k )
	: core::InternalGearRatios( k )
{
}

bool InternalGearRatios::next()
{
	if ( m_combi.next() )
	{
		m_K = m_combi.get();
		return true;
	}
	return false;
}

const NS_CORE InternalGearRatioValue InternalGearRatios::operator[]( size_t i ) const
{
	return m_K[i];
}
