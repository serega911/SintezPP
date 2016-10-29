#include "Range.h"

NS_CORE_USING

const Range::T core::Range::s_eps = T( 0.0001 );

Range::Range( const T beg, const T end )
	: m_begin( beg )
	, m_end( end )
{
}

Range::T Range::getBegin() const
{
	return m_begin;
}

Range::T Range::getEnd() const
{
	return m_end;
}

Range::T Range::getMid() const
{
	return T( ( m_begin + m_end ).getValue() / 2.0f );
}

bool Range::isInRange( const T value ) const
{
	return value >= m_begin - s_eps && value <= m_end + s_eps;
}
