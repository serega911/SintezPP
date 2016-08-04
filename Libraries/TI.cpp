#include <iostream>

#include "TI.h"
#include "TSingletons.h"
#include "TLog.h"

NS_CORE_USING

double TI::m_eps = 0.05;

TI::TI( const std::vector<TIValue>& i, double eps )
	: m_i( i )
{
}

TI::TI()
{
}

int TI::size() const
{
	return m_i.size();
}

const TIValue & TI::operator[]( size_t i ) const
{
	return m_i.at(i);
}

void TI::operator=(const TI& obj)
{
	m_i = obj.m_i;
	m_eps = obj.m_eps;
}

void TI::push_back( TIValue value )
{
	m_i.push_back(value);
}

void TI::print() const
{
	TLog::log( "eps = " + std::to_string( m_eps ) );
	for (auto& it: m_i)
		TLog::log( std::to_string( it ) + " ", false );
	TLog::log( "" );
}

bool TI::findIn( TIValue value ) const
{
	if ( m_i.size() == TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears )
	{
		for ( auto& it : m_i )
		{
			if ( abs( it - value ) <= m_eps )
				return true;
		}
		return false;
	}
	else
		return true;
}

bool TI::operator==( const TI& obj ) const
{
	if (m_i.size() <= obj.size())
	{
		for (auto& it : m_i)
		{
			bool finded = false;
			for (auto& jt : obj.m_i)
			{
				if (abs(it - jt) <= m_eps)
					finded = true;
			}
			if (finded == false)
				return false;
		}
		return true;
	}
	else
	{
		for (auto& it : obj.m_i)
		{
			bool finded = false;
			for (auto& jt : m_i)
			{
				if (abs(it - jt) <= m_eps)
					finded = true;
			}
			if (finded == false)
				return false;
		}
		return true;
	}
}
