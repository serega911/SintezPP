#include <iostream>

#include "TI.h"
#include "TSingletons.h"
#include "TLog.h"

NS_CORE_USING

TIValue TI::m_eps = TIValue( 0.01 );

TI::TI( const TIValueArray& i, TIValue eps )
	: m_i( i )
{
}

TI::TI()
{
}

size_t TI::size() const
{
	return m_i.size();
}

bool core::TI::loadFromFile( std::istream& file )
{
	return false;
}

void core::TI::writeToFile( std::ostream& file ) const
{
	for ( auto& it : m_i )
		file << it.getValue() << ' ';
}

const TIValue & TI::operator[]( size_t i ) const
{
	return m_i.at( i );
}

void TI::operator=( const TI& obj )
{
	m_i = obj.m_i;
	m_eps = obj.m_eps;
}

void TI::push_back( TIValue value )
{
	m_i.push_back( value );
}

void TI::print() const
{
	TLog::log( "eps = " + std::to_string( m_eps.getValue() ) );
	for ( auto& it : m_i )
		TLog::log( std::to_string( it.getValue() ) + " ", false );
	TLog::log( "" );
}

bool TI::findIn( TIValue value ) const
{
	if ( m_i.size() == TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears )
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

bool TI::operator==( const TI& obj ) const
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
					finded = true;
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
