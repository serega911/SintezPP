#pragma once

#include "Cordinates.h"
#include <vector>

#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class Route
{
private:

	std::vector<Cordinate>					m_route;

public:

	size_t										size();

	void										addCordinates( const Cordinate & cordinates );

	Cordinate									operator[]( size_t pos );

};

NS_ARI_END


