#pragma once

#include "Combinatorics.h"

NS_CORE_START

template <typename T>
class Subset : public Combinatorics<T>
{
public:

	Subset( const T& values, const size_t k )
	{
		init( values, k );
	}

	bool next() override
	{
		const size_t k = m_indexes.size();
		const size_t n = m_values.size();
		const size_t delta = n - k;

		if ( n == 0 || k == 0 || n < k )
			return false;
		
		if ( m_indexes[k - 1] < n - 1 )
		{
			m_indexes[k - 1]++;
		}
		else
		{
			int pos = 1;

			for ( size_t i = 1; i < k; i++ )
			{
				if ( m_indexes[i] > i + delta - 1 )
				{
					pos = i;
					break;
				}
			}

			m_indexes[pos - 1]++;
			for ( size_t i = pos; i < k; i++ )
				m_indexes[i] = m_indexes[i - 1] + 1;
		}

		if ( m_indexes[0] > delta )
			return false;
		return true;
	}

	virtual int getCount() override
	{
		const size_t k = m_indexes.size();
		const size_t n = m_values.size();
		return getCount( n, k );
	}

	static int getCount(const int n, const int k)
	{
		return factorial( n ) / ( factorial( k ) * factorial( n - k ) );
	}
};

NS_CORE_END