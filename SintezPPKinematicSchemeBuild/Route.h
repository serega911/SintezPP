#pragma once

#include "Cordinates.h"
#include <vector>

#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class Route
{
private:

	std::vector<Cordinates>					m_route;

public:

	size_t										size();

	void										addCordinates( const Cordinates & cordinates );

	Cordinates									operator[]( size_t pos );

};

NS_ARI_END


