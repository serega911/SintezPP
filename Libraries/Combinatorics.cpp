#include <algorithm>

#include "Combinatorics.h"

NS_CORE_USING

Combinatorics::Combinatorics()
{
}

core::Combinatorics::~Combinatorics()
{
	int a = 5;
	this;
}

Combinatorics* Combinatorics::getInstance()
{
	static Combinatorics obj;
	return &obj;
}

template <typename T>
inline bool getCombi( T key, std::map<T, std::vector<CombinatoricsValueArray>>& container, const std::function<void()>& toCall, CombinatoricsValueArray& mas, size_t i )
{
	auto subset = container.find( key );

	if ( subset == container.end() )
	{
		toCall();
		subset = container.find( key );
	}

	if ( i < subset->second.size() )
	{
		mas = subset->second[i];
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
inline size_t getCombiCount( T key, std::map<T, std::vector<CombinatoricsValueArray>>& container, const std::function<void()>& toCall )
{
	auto subset = container.find( key );

	if ( subset == container.end() )
	{
		toCall();
	}

	subset = container.find( key );

	return subset->second.size();
}

bool core::Combinatorics::getSubset( const size_t n, const size_t k, const size_t i, CombinatoricsValueArray & mas )
{
	if ( 0 == n )
	{
		return false;
	}
	else
	{
		const auto key = std::pair<size_t, size_t>( n, k );
		return getCombi( key, m_subsets, std::bind( &Combinatorics::createSubset, this, key ), mas, i );
	}
}

bool core::Combinatorics::getPremutation( const size_t n, const size_t i, CombinatoricsValueArray & mas )
{
	if ( 0 == n )
	{
		return false;
	}
	else
	{
		return getCombi( n, m_premutations, std::bind( &Combinatorics::createPremutation, this, n ), mas, i );
	}
}

bool core::Combinatorics::getOrderedSample( const size_t n, const size_t k, const size_t i, CombinatoricsValueArray & mas )
{
	if ( 0 == n )
	{
		return false;
	}
	else
	{
		const auto key = std::pair<size_t, size_t>( n, k );
		return getCombi( key, m_orderedSamples, std::bind( &Combinatorics::createOrderedSample, this, key ), mas, i );
	}
}

size_t core::Combinatorics::getPremutationsCount( const size_t n )
{
	return getCombiCount( n, m_premutations, std::bind( &Combinatorics::createPremutation, this, n ) );
}

size_t core::Combinatorics::getSubsetsCount( const size_t n, const size_t k )
{
	auto key = std::pair<size_t, size_t>( n, k );
	return getCombiCount( key, m_subsets, std::bind( &Combinatorics::createSubset, this, key ) );
}

size_t core::Combinatorics::getOrderedSamplesCount( const size_t n, const size_t k )
{
	auto key = std::pair<size_t, size_t>( n, k );
	return getCombiCount( key, m_orderedSamples, std::bind( &Combinatorics::createOrderedSample, this, key ) );
}

void Combinatorics::createPremutation( const size_t n )
{
	CombinatoricsValueArray premutation;
	premutation.resize( n );
	for ( size_t i = 0; i < n; i++ )
	{
		premutation[i] = i;
	}

	do
	{
		m_premutations[n].emplace_back( premutation );
	} while ( std::next_permutation( premutation.begin(), premutation.end() ) );
}

void core::Combinatorics::createOrderedSample( const std::pair<size_t, size_t> key )
{
	CombinatoricsValueArray subset;
	subset.resize( key.second, 0 );

	do
	{
		m_orderedSamples[key].emplace_back( subset );
	} while ( nextOrderedSample( key.first, subset ) );
}

void Combinatorics::createSubset( const std::pair<size_t, size_t> key )
{
	CombinatoricsValueArray subset;
	subset.resize( key.second );
	for ( size_t i = 0; i < key.second; i++ )
	{
		subset[i] = i;
	}

	do
	{
		m_subsets[key].emplace_back( subset );
	} while ( nextSubset( key.first, subset ) );
}

bool core::Combinatorics::nextOrderedSample( const size_t n, CombinatoricsValueArray & mas )
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

bool core::Combinatorics::nextSubset( const size_t n, CombinatoricsValueArray & mas )
{
	if ( mas.size() == 0 )
		return false;
	CombinatoricsValueArray tmp;
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