#pragma once

#include <vector>

#include "GlobalDefines.h"
#include "InternalGearRatioValue.h"

NS_CORE_START

class Range
{
private:

	typedef InternalGearRatioValue T;

	static const T								s_eps;

	T											m_begin;
	T											m_end;

public:

	Range() = delete;
	Range( const T beg, const T end );

	T											getBegin() const;
	T											getEnd() const;
	T											getMid() const;
	bool										isInRange( const T value ) const;
	
};

NS_CORE_END
