#pragma once

#include"Log.h"
#include "Combinatorics.h"

NS_CORE_START

template <typename T>
class OrderedSample : public Combinatorics<T>
{
public:

	OrderedSample()
	{
	}

	OrderedSample( const T& values, const size_t k )
	{
		init( values, k );
	}

	virtual void init( const T& values, const size_t k ) override
	{
		m_values = values;

		m_indexes.resize( k );
		for ( size_t i = 0; i < k; i++ )
			m_indexes[i] = 0;
	}

	bool next() override
	{
		const size_t min_value = 0;
		const size_t k = m_indexes .size();
		const size_t n = m_values.size();

		for ( int i = k - 1; i >= 0; --i )
		{
			if ( m_indexes[i] < n - 1 )
			{
				++m_indexes[i];
				return true;
			}
			else
			{
				m_indexes[i] = min_value;
			}
		}

		return false;
	}

	virtual int getCount() override
	{
		Log::warning( true, "Not implemented", Log::CRITICAL, HERE );
		return 0;
	}
};

NS_CORE_END