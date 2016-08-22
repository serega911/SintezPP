#pragma once

#include <vector>

#include "GlobalDefines.h"

NS_CORE_START

class TCombinations
{
private:

	std::vector<int>							m_container;

public:

	void										init( int count );
	bool										nextReplace( int maxValue );
	const std::vector<int>&						getReplace() const;
	int											operator[]( int i ) const;
	int											size() const;

};

NS_CORE_END