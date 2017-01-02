#pragma once

#include <memory>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/eMainElement.h"

#include "Cordinate.h"

NS_ARI_START



class ISchemeCell
{
public:

	virtual const Cordinate&					getCord() const = 0;
	virtual bool								isConsist( const NS_CORE eMainElement& obj ) const = 0;

};

typedef std::shared_ptr<ISchemeCell> ISchemeCell_p;

NS_ARI_END