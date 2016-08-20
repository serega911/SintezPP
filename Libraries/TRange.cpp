#include "TRange.h"

NS_CORE_USING

TRange::TRange( const double beg, const double end )
	: m_begin( beg )
	, m_end( end )
{
}

double TRange::getBegin() const
{
	return m_begin;
}

double TRange::getEnd() const
{
	return m_end;
}

double TRange::getMid() const
{
	return ( m_begin + m_end ) / 2.0f;
}

bool TRange::isInRange( const double value ) const
{
	return value >= m_begin && value <= m_end;
}
