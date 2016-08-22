#pragma once

#include "TCordinates.h"
#include <vector>

#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class TRoute
{
private:

	std::vector<TCordinates>					m_route;

public:

	size_t										size();

	void										addCordinates( const TCordinates & cordinates );

	TCordinates									operator[]( size_t pos );

};

NS_ARI_END


