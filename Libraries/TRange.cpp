#include "TRange.h"

NS_CORE_USING

const TRange::T core::TRange::s_eps = T( 0.0001 );

TRange::TRange( const T beg, const T end )
	: m_begin( beg )
	, m_end( end )
{
}

TRange::T TRange::getBegin() const
{
	return m_begin;
}

TRange::T TRange::getEnd() const
{
	return m_end;
}

TRange::T TRange::getMid() const
{
	return T( ( m_begin + m_end ).getValue() / 2.0f );
}

bool TRange::isInRange( const T value ) const
{
	return value >= m_begin - s_eps && value <= m_end + s_eps;
}
