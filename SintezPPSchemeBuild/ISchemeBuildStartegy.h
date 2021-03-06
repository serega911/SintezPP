#pragma once

#include <memory>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Code.h"
#include "IScheme.h"
#include "ITraceStrategy.h"

NS_ARI_START

class ISchemeBuildStartegy
{
public:

	virtual bool								run( IScheme_p & scheme, ITraceStrategy_p & strategy, const NS_CORE Code& code ) = 0;

};

typedef std::shared_ptr<ISchemeBuildStartegy> ISchemeBuildStartegy_p;

NS_ARI_END