#pragma once

#include <algorithm>

#include "Combinatorics.h"

NS_CORE_START

template <typename T>
class Permutation: public Combinatorics<T>
{
private:



public:

	Permutation( const T &values )
	{
		init( values );
	}

	void init( const T &values )
	{
		Combinatorics::init( values, values.size() );
	}

	bool next() override
	{
		return std::next_permutation( m_indexes.begin(), m_indexes.end() );
	}

	virtual int getCount() override
	{
		Log::warning( true, "Not implemented", Log::CRITICAL, HERE );
		return 0;
	}
};

NS_CORE_END