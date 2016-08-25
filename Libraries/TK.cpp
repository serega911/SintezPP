#include <iostream>
#include <algorithm>

#include "TK.h"
#include "func_lib.h"
#include "TSingletons.h"
#include "TLog.h"

NS_CORE_USING

TK::TK( const TKValueArray& k )
	: m_K(k)
{
}

core::TK::TK()
{
}

core::TK::TK( const size_t size )
{
	m_K.resize( size );
}

const TKValue TK::operator[]( size_t i ) const
{
	return m_K.at(i);
}

void TK::print() const
{
	for ( auto &it : m_K )
	{
		TLog::log( it.getValue(), false );
		TLog::log( " ", false );
	}
}

size_t TK::size() const
{
	return m_K.size();
}

void TK::writeToFile(std::ostream& file) const
{
	for (auto& it : m_K)
		file << it.getValue() << ' ';
}

void TK::setValues( const TKValueArray& values )
{
	m_K = values;
}

bool TK::check() const
{
	const auto& initialData = TSingletons::getInstance()->getInitialData();
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
bool TK::loadFromFile(std::istream& in)
{
	m_K.resize( TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	for ( size_t i = 0; i < m_K.size(); i++ )
	{
		double value;
		in >> value;
		m_K[i] = TKValue( value );
	}

	return true;
}

