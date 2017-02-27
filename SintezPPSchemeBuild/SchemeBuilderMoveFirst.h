#pragma once

#include "ISchemeBuildStartegy.h"

NS_ARI_START

class SchemeBuilderMoveFirst;

typedef std::shared_ptr<SchemeBuilderMoveFirst> SchemeBuilderMoveFirst_p;

class SchemeBuilderMoveFirst : public ISchemeBuildStartegy
{
	SchemeBuilderMoveFirst();

public:

	static SchemeBuilderMoveFirst_p				create();

	virtual bool								run( IScheme_p & scheme, ITraceStrategy_p & strategy, const NS_CORE Code& code ) override;

};



NS_ARI_END