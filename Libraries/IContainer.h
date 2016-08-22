#pragma once

#include <iostream>
#include "GlobalDefines.h"

NS_CORE_START

class IContainer
{
public:
	virtual size_t								size() const = 0;
	virtual void								writeToFile( std::ostream& ) const = 0;
	virtual bool								loadFromFile( std::istream& ) = 0;
};

NS_CORE_END
