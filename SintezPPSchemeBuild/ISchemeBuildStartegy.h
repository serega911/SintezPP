#pragma once

#include <memory>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Code.h"
#include "IScheme.h"
#include "IPathBuildStartegy.h"

NS_ARI_START

class ISchemeBuildStartegy
{
public:

	virtual void								run( IScheme_p & scheme, IPathBuildStartegy_p & strategy, const NS_CORE Code& code ) = 0;

};

typedef std::shared_ptr<ISchemeBuildStartegy> ISchemeBuildStartegy_p;

NS_ARI_END