#include <iostream>
#include <algorithm>

#include "TK.h"
#include "func_lib.h"
#include "TSingletons.h"
#include "TLog.h"

NS_CORE_USING

const TKValue TK::operator[]( size_t i ) const
{
	return m_K.at(i);
}

void TK::print() const
{
	for (auto &it : m_K)
		TLog::log( std::to_string( it ) + " ", false );
	TLog::log( "", false );
}

size_t TK::size() const
{
	return m_K.size();
}

void TK::setFinded( const bool finded )
{
	m_isFinded = finded;
}

bool TK::getFinded() const
{
	return m_isFinded;
}

void TK::writeToFile(std::ostream& file) const
{
	for (auto& it : m_K)
		file << it << ' ';
}

bool TK::loadFromFile(std::istream& file )
{
	return true;
}

void TK::setValues( const std::vector<TKValue>& values )
{
	m_K = values;
}

bool TK::check() const
{
	const auto& initialData = TSingletons::getInstance()->getInitialData();

	for ( auto i = 0; i < m_K.size(); i++ )
	{
		bool flag = false;
		for ( auto j = 0; j < initialData._ranges.size(); j++ )
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

	return true;
}

