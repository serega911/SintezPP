#pragma once

#include <memory>
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class ICommand;

typedef std::shared_ptr<ICommand> ICommand_p;

class ICommand
{
public:

	virtual int 								execute() const = 0;

};


NS_ARI_END