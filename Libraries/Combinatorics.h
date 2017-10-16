#pragma once
#include <vector>

#include "GlobalDefines.h"

NS_CORE_START

template <typename T>
class Combinatorics
{
protected:

	typedef std::vector<size_t> Combinations;

	T											m_values;
	Combinations								m_indexes;

	static long factorial( const int n )
	{
		long ans = ((n == 0) ? 0 : 1);

		for ( int i = 1; i < n; i++ )
			ans *= i;

		return ans;
	}

public:

	virtual bool								next() = 0;
	virtual int									getCount() = 0;

	Combinatorics()
	{
	}

	Combinatorics( const T& values, const size_t k )
	{
		init( values, k );
	}

	virtual void init( const T& values, const size_t k )
	{
		m_values = values;

		m_indexes.resize( k );
		for ( size_t i = 0; i < k; i++ )
			m_indexes[i] = i;
	}

	T get() const
	{
		T ans;
		for ( const auto &it : m_indexes )
			ans.emplace_back( m_values.at( it ) );
		return ans;
	}

};

NS_CORE_END