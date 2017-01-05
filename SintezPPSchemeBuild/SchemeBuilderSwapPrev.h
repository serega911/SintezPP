#pragma once

#include "ISchemeBuildStartegy.h"

NS_ARI_START

class SchemeBuilderSwapPrev;

typedef std::shared_ptr<SchemeBuilderSwapPrev> SchemeBuilderSwapPrev_p;

class SchemeBuilderSwapPrev: public ISchemeBuildStartegy
{
	SchemeBuilderSwapPrev();

public:

	static SchemeBuilderSwapPrev_p				create();

	virtual void								run( IScheme_p & scheme, IPathBuildStartegy_p & strategy, const NS_CORE Code& code ) override;

};



NS_ARI_END