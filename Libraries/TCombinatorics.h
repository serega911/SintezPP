#pragma once

#include <map>
#include <functional>

#include "GlobalDefines.h"
#include "TCombinatoricsValueArray.h"

NS_CORE_START

class TCombinatorics
{
private:

	TCombinatorics( const TCombinatorics& obj ) = delete;
	TCombinatorics();

	std::map<size_t,					std::vector<TCombinatoricsValueArray>>		m_premutations;
	std::map<std::pair<size_t, size_t>, std::vector<TCombinatoricsValueArray>>		m_subsets;
	std::map<std::pair<size_t, size_t>, std::vector<TCombinatoricsValueArray>>		m_orderedSamples;

	bool										nextSubset( const size_t n, TCombinatoricsValueArray & mas );
	bool										nextOrderedSample( const size_t n, TCombinatoricsValueArray & mas );

 	void										createSubset( std::pair<size_t, size_t> key );
 	void										createPremutation( const size_t n );
 	void										createOrderedSample( std::pair<size_t, size_t> key );


public:

	static TCombinatorics*						getInstance();

	bool										getPremutation( const size_t n, const size_t i, TCombinatoricsValueArray & mas );						//перестановки
	bool										getSubset( const size_t n, const size_t k, const size_t i, TCombinatoricsValueArray & mas );			//сочетания
	bool										getOrderedSample( const size_t n, const size_t k, const size_t i, TCombinatoricsValueArray & mas );		//размещения

	~TCombinatorics();
};

NS_CORE_END