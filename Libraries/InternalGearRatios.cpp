#include <iostream>
#include <algorithm>

#include "InternalGearRatios.h"
#include "Singletons.h"
#include "Log.h"

NS_CORE_USING

InternalGearRatios::InternalGearRatios( const InternalGearRatioValueArray& k )
: m_K( k )
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
	return m_K.at( i );
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

void InternalGearRatios::writeToFile( std::ostream& file ) const
{
	for ( auto& it : m_K )
		file << it.getValue() << ' ';
}

void InternalGearRatios::setValues( const InternalGearRatioValueArray& values )
{
	m_K = values;
}

bool InternalGearRatios::check() const
{
	const auto& initialData = Singletons::getInstance()->getInitialData();
	const size_t kSize = m_K.size();
	const size_t rangesSize = initialData._ranges.size();

	for ( size_t i = 0; i < kSize; i++ )
	{
		bool flag = false;
		for ( size_t j = 0; j < rangesSize; j++ )
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

	return kSize > 0;
}
bool InternalGearRatios::loadFromFile( std::istream& in )
{
	const size_t kSize = Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	m_K.resize( kSize );

	for ( size_t i = 0; i < kSize; i++ )
	{
		float value;
		in >> value;
		m_K[i] = InternalGearRatioValue( value );
	}

	return true;
}

