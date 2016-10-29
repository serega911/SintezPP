#include <iostream>
#include <algorithm>

#include "InternalGearRatios.h"
#include "func_lib.h"
#include "Singletons.h"
#include "Log.h"

NS_CORE_USING

InternalGearRatios::InternalGearRatios( const InternalGearRatioValueArray& k )
	: m_K(k)
{
}

core::InternalGearRatios::InternalGearRatios()
{
}

core::InternalGearRatios::InternalGearRatios( const size_t size )
{
	m_K.resize( size );
}

const InternalGearRatioValue InternalGearRatios::operator[]( size_t i ) const
{
	return m_K.at(i);
}

void InternalGearRatios::print() const
{
	for ( auto &it : m_K )
	{
		Log::log( it.getValue(), false );
		Log::log( " ", false );
	}
}

size_t InternalGearRatios::size() const
{
	return m_K.size();
}

void InternalGearRatios::writeToFile(std::ostream& file) const
{
	for (auto& it : m_K)
		file << it.getValue() << ' ';
}

void InternalGearRatios::setValues( const InternalGearRatioValueArray& values )
{
	m_K = values;
}

bool InternalGearRatios::check() const
{
	const auto& initialData = Singletons::getInstance()->getInitialData();
	for ( size_t i = 0; i < m_K.size(); i++ )
	{
		bool flag = false;
		for ( size_t j = 0; j < initialData._ranges.size(); j++ )
		{
			if ( initialData._ranges[j].isInRange( m_K[i] ) )
			{
				flag = true;
				break;
			}
		}

		if ( !flag )
		{
			return false;
		}
	}

	return true && m_K.size();
}
bool InternalGearRatios::loadFromFile(std::istream& in)
{
	m_K.resize( Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	for ( size_t i = 0; i < m_K.size(); i++ )
	{
		double value;
		in >> value;
		m_K[i] = InternalGearRatioValue( value );
	}

	return true;
}

