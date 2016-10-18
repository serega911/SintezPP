#pragma once

#include <iostream>
#include "GlobalDefines.h"

NS_CORE_START

class IIOItem
{
public:
	virtual void								writeToFile( std::ostream& ) const = 0;
	virtual bool								loadFromFile( std::istream& ) = 0;
};

NS_CORE_END
