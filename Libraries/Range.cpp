#include "Range.h"

NS_CORE_USING

const Range::T core::Range::s_eps = T( 0.0001f );

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

bool core::Range::operator==( const Range& obj ) const
{
	return obj.m_begin == m_begin && obj.m_end == m_end;
}

bool core::Range::loadFromFile( std::istream& file )
{
	if ( file.eof() )
		return false;

	float begin, end;

	file >> begin >> end;

	m_begin = T( begin );
	m_end = T( end );

	bool aret = file.eof();

	return true;
}

void core::Range::writeToFile( std::ostream& file ) const
{
	file << m_begin.getValue() << ' ' << m_end.getValue();
}
