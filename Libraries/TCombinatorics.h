#pragma once

#include <map>

#include "GlobalDefines.h"
#include "TCombinatoricsValueArray.h"

NS_CORE_START

class TCombinatorics
{
private:

	TCombinatorics( const TCombinatorics& obj ) = delete;
	TCombinatorics();

	std::map<size_t, std::vector<TCombinatoricsValueArray>>							m_premutations;
	std::map<std::pair<size_t, size_t>, std::vector<TCombinatoricsValueArray>>		m_subsets;
	std::map<std::pair<size_t, size_t>, std::vector<TCombinatoricsValueArray>>		m_orderedSamples;

	bool										nextSubset( const size_t n, TCombinatoricsValueArray & mas );
	bool										nextOrderedSample( const size_t n, TCombinatoricsValueArray & mas );


public:

	static TCombinatorics*						getInstance();

	bool										getPremutation( const size_t n, const size_t i, TCombinatoricsValueArray & mas );		//перестановки
	bool										getSubset( const size_t n, const size_t k, const size_t i, TCombinatoricsValueArray & mas );		//сочетания
	bool										getOrderedSample( const size_t n, const size_t k, const size_t i, TCombinatoricsValueArray & mas );		//размещения

};

NS_CORE_END