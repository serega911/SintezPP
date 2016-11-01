#include <iostream>

#include "Ratios.h"
#include "Singletons.h"
#include "Log.h"

NS_CORE_USING

RatioValue Ratios::m_eps = RatioValue( 0.01 );

Ratios::Ratios( const RatioValueArray& i, RatioValue eps )
	: m_i( i )
{
}

Ratios::Ratios()
{
}

size_t Ratios::size() const
{
	return m_i.size();
}

bool core::Ratios::loadFromFile( std::istream& file )
{
	return false;
}

void core::Ratios::writeToFile( std::ostream& file ) const
{
	for ( auto& it : m_i )
		file << it.getValue() << ' ';
}

const RatioValue & Ratios::operator[]( size_t i ) const
{
	return m_i.at( i );
}

void Ratios::operator=( const Ratios& obj )
{
	m_i = obj.m_i;
	m_eps = obj.m_eps;
}

void Ratios::push_back( RatioValue value )
{
	m_i.push_back( value );
}

void Ratios::print() const
{
	Log::log( "eps = " + std::to_string( m_eps.getValue() ) );
	for ( auto& it : m_i )
		Log::log( std::to_string( it.getValue() ) + " ", false );
	Log::log( "" );
}

bool Ratios::findIn( RatioValue value ) const
{
	if ( m_i.size() == Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears )
	{
		for ( auto& it : m_i )
		{
			if ( ( it - value ).getAbs() <= m_eps )
				return true;
		}
		return false;
	}
	else
		return true;
}

bool Ratios::operator==( const Ratios& obj ) const
{
	if ( m_i.size() == 0 || obj.size() == 0 )
		return false;

	if ( m_i.size() <= obj.size() )
	{
		for ( auto& it : m_i )
		{
			bool finded = false;
			for ( auto& jt : obj.m_i )
			{
				if ( ( it - jt ).getAbs() <= m_eps )
				{
					finded = true;
					break;
				}
			}
			if ( finded == false )
				return false;
		}
		return true;
	}
	else
	{
		for ( auto& it : obj.m_i )
		{
			bool finded = false;
			for ( auto& jt : m_i )
			{
				if ( ( it - jt ).getAbs() <= m_eps )
					finded = true;
			}
			if ( finded == false )
				return false;
		}
		return true;
	}
}
