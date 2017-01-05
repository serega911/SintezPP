#pragma once

#include <memory>
#include <vector>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Element.h"
#include "ISchemeElement.h"
#include "Cordinate.h"

NS_ARI_START

class IPathBuildStartegy
{
public:
	
	virtual void								init( const std::vector<ISchemeElement_p>& elements ) = 0;
	
	virtual std::vector<Cordinate>				run( NS_CORE Element& start, NS_CORE Element& finish ) = 0;

};

typedef std::shared_ptr<IPathBuildStartegy> IPathBuildStartegy_p;

NS_ARI_END




