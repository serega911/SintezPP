#pragma once

#include <vector>

#include "GlobalDefines.h"
#include "TKValue.h"

NS_CORE_START

class TRange
{
private:

	typedef TKValue T;

	static const T								s_eps;

	T											m_begin;
	T											m_end;

public:

	TRange() = delete;
	TRange( const T beg, const T end );

	T											getBegin() const;
	T											getEnd() const;
	T											getMid() const;
	bool										isInRange( const T value ) const;
	
};

NS_CORE_END
