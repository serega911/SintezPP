#pragma once

#include <memory>

#include "../Libraries/GlobalDefines.h"


NS_ARI_START

class ICommand
{
public:

	virtual bool								execute() = 0;
	virtual bool								apply() = 0;
	virtual bool								isApplied() = 0;

};

typedef std::shared_ptr<ICommand> ICommand_p;

NS_ARI_END