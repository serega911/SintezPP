#include "TCombinations.h"

NS_CORE_USING

void TCombinations::init( size_t count )
{
	m_container.clear();
	m_container.reserve( count );

	for ( size_t i = 0; i < count; i++ )
		m_container.push_back( i );
}

bool TCombinations::nextReplace( T maxValue )
{
	if ( m_container.size() == 0 )
		return false;
	std::vector<T>tmp;
	size_t m = m_container.size(); // RK: empty lines for logic blocks?
	tmp = m_container;
	int x = 1;
	if ( tmp[m - 1] < maxValue )
		tmp[m - 1]++;
	else
	{
		if ( m == 1 ) return false;
		for ( size_t i = 1; i < m; i++ )
			if ( tmp[i] > i + maxValue - m ){
				x = i;
				break;
			}
		tmp[x - 1]++;
		for ( size_t i = x; i < m; i++ )
			tmp[i] = tmp[i - 1] + 1;
	}
	if ( tmp[0] > maxValue - m + 1 )
	{
		return false;
	}
	m_container = tmp;
	return true;
}

const std::vector<int>& TCombinations::getReplace() const
{
	return m_container;
}

size_t TCombinations::size() const
{
	return m_container.size();
}

TCombinations::T TCombinations::operator[]( size_t i ) const
{
	return m_container.at( i );
}
