#include <algorithm>

#include "TCombinatorics.h"
#include "TCombinations.h"

NS_CORE_USING

TCombinatorics::TCombinatorics()
{

}

bool core::TCombinatorics::nextOrderedSample( const size_t n, TCombinatoricsValueArray & mas )
{
	size_t min_value = 0;
	size_t k = mas.size();

	for ( int i = k - 1; i >= 0; --i )
	{
		if ( mas[i] < n - 1 )
		{
			++mas[i];
			return true;
		}
		else
		{
			mas[i] = min_value;
		}
	}

	return false;
}

bool core::TCombinatorics::nextSubset( const size_t n, TCombinatoricsValueArray & mas )
{
	if ( mas.size() == 0 )
		return false;
	TCombinatoricsValueArray tmp;
	size_t m = mas.size(); // RK: empty lines for logic blocks?
	tmp = mas;
	int x = 1;
	if ( tmp[m - 1] < n - 1 )
		tmp[m - 1]++;
	else
	{
		if ( m == 1 ) return false;
		for ( size_t i = 1; i < m; i++ )
			if ( tmp[i] > i + n - 1 - m ){
				x = i;
				break;
			}
		tmp[x - 1]++;
		for ( size_t i = x; i < m; i++ )
			tmp[i] = tmp[i - 1] + 1;
	}
	if ( tmp[0] > n - 1 - m + 1 )
	{
		return false;
	}
	mas = tmp;
	return true;
}

TCombinatorics* TCombinatorics::getInstance()
{
	static TCombinatorics obj;
	return &obj;
}

bool core::TCombinatorics::getSubset( const size_t n, const size_t k, const size_t i, TCombinatoricsValueArray & mas )
{
	bool result = true;

	auto key = std::pair<size_t, size_t>( n, k );
	auto premutations = m_subsets.find( key );

	if ( premutations == m_subsets.end() )
	{
		TCombinatoricsValueArray subset;
		subset.resize( k );
		for ( size_t i = 0; i < k; i++ )
		{
			subset[i] = i;
		}

		do
		{
			m_subsets[key].emplace_back( subset );
		} while ( nextSubset( n, subset ) );

		premutations = m_subsets.find( key );
	}

	if ( i < premutations->second.size() )
	{
		mas = premutations->second[i];
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

bool core::TCombinatorics::getPremutation( const size_t n, const size_t i, TCombinatoricsValueArray & mas )
{
	bool result = true;

	auto premutations = m_premutations.find( n );

	if ( premutations == m_premutations.end() )
	{
		TCombinatoricsValueArray premutation;
		premutation.resize( n );
		for ( size_t i = 0; i < n; i++ )
		{
			premutation[i] = i;
		}
			
		do
		{
			m_premutations[n].emplace_back( premutation );
		} while ( std::next_permutation( premutation.begin(), premutation.end() ) );

		premutations = m_premutations.find( n );
	}

	if ( i < premutations->second.size() )
	{
		mas = premutations->second[i];
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

bool core::TCombinatorics::getOrderedSample( const size_t n, const size_t k, const size_t i, TCombinatoricsValueArray & mas )
{
	bool result = true;

	auto key = std::pair<size_t, size_t>( n, k );
	auto orderedSamples = m_orderedSamples.find( key );

	if ( orderedSamples == m_orderedSamples.end() )
	{
		TCombinatoricsValueArray subset;
		subset.resize( k, 0 );

		do
		{
			m_orderedSamples[key].emplace_back( subset );
		} while ( nextOrderedSample( n, subset ) );

		orderedSamples = m_orderedSamples.find( key );
	}

	if ( i < orderedSamples->second.size() )
	{
		mas = orderedSamples->second[i];
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}


