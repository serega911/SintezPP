#include "TRange.h"

NS_CORE_USING

TRange::TRange( const float beg, const float end )
	: m_begin( beg )
	, m_end( end )
{
}

float TRange::getBegin() const
{
	return m_begin;
}

float TRange::getEnd() const
{
	return m_end;
}

float TRange::getMid() const
{
	return ( m_begin + m_end ) / 2.0f;
}

bool TRange::isInRange( const float value ) const
{
	return value >= m_begin && value <= m_end;
}
