#include "TRange.h"

using namespace pss;

pss::TRange::TRange( const float beg, const float end )
	: m_begin( beg )
	, m_end( end )
{

}

float pss::TRange::getBegin() const
{
	return m_begin;
}

float pss::TRange::getEnd() const
{
	return m_end;
}

float pss::TRange::getMid() const
{
	return ( m_begin + m_end ) / 2.0f;
}

bool pss::TRange::isInRange( const float value )
{
	return value > m_begin && value < m_end;
}
