#pragma once

#include <memory>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/eColor.h"

#include "Cordinate.h"

NS_ARI_START

class IDisplay
{
public:
	virtual void								print( const Cordinate& cord, const char c ) const = 0;
	virtual void								setColors( NS_CORE eColor font, NS_CORE eColor background ) = 0;
	virtual void								resetColors() = 0;
};

typedef std::shared_ptr<IDisplay> IDisplay_p;

NS_ARI_END