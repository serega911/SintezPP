#pragma once

#include <map>
#include <functional>

#include "GlobalDefines.h"
#include "CombinatoricsValueArray.h"

NS_CORE_START

class Combinatorics
{
private:

	Combinatorics( const Combinatorics& obj ) = delete;
	Combinatorics();

	std::map<size_t,					std::vector<CombinatoricsValueArray>>		m_premutations;
	std::map<std::pair<size_t, size_t>, std::vector<CombinatoricsValueArray>>		m_subsets;
	std::map<std::pair<size_t, size_t>, std::vector<CombinatoricsValueArray>>		m_orderedSamples;

	bool										nextSubset( const size_t n, CombinatoricsValueArray & mas );
	bool										nextOrderedSample( const size_t n, CombinatoricsValueArray & mas );

 	void										createSubset( std::pair<size_t, size_t> key );
 	void										createPremutation( const size_t n );
 	void										createOrderedSample( std::pair<size_t, size_t> key );


public:

	static Combinatorics*						getInstance();

	bool										getPremutation( const size_t n, const size_t i, CombinatoricsValueArray & mas );						//������������
	bool										getSubset( const size_t n, const size_t k, const size_t i, CombinatoricsValueArray & mas );			//���������
	bool										getOrderedSample( const size_t n, const size_t k, const size_t i, CombinatoricsValueArray & mas );		//����������

	~Combinatorics();
};

NS_CORE_END