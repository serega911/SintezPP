#pragma once

#include <vector>

#include "GlobalDefines.h"

NS_CORE_START

class TCombinations
{
private:

	typedef int T;

	std::vector<T>								m_container;

public:

	void										init( size_t count );
	bool										nextReplace( T maxValue );
	const std::vector<T>&						getReplace() const;
	T											operator[]( size_t i ) const;
	size_t										size() const;

};//C(n,k) - сочетания

NS_CORE_END