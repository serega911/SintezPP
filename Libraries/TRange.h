#pragma once

#include <vector>
#include "GlobalDefines.h"

NS_CORE_START

class TRange;
typedef std::vector<TRange> TRangeArray;

class TRange
{
private:

	double										m_begin;
	double										m_end;

public:

	TRange() = delete;
	TRange( const double beg, const double end );

	double										getBegin() const;
	double										getEnd() const;
	double										getMid() const;
	bool										isInRange( const double value ) const;
	
};

NS_CORE_END
