#pragma once

#include "IPathBuildStartegy.h"

NS_ARI_START

class PathBuilderLee;

typedef std::shared_ptr<PathBuilderLee> PathBuilderLee_p;

class PathBuilderLee: public IPathBuildStartegy
{
private:

	PathBuilderLee();

public:

	static PathBuilderLee_p						create();

	virtual void								init( const std::vector<ISchemeElement_p>& elements ) override;

	virtual std::vector<Cordinate>				run( NS_CORE Element& start, NS_CORE Element& finish ) override;

};



NS_ARI_END