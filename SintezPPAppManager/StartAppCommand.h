#pragma once

#include <string>

#include "ICommand.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class StartAppCommand;

typedef std::shared_ptr<StartAppCommand> StartAppCommand_p;

class StartAppCommand : public ICommand
{
private:

	std::string									m_command;

public:

	StartAppCommand( const std::string appName );

	void										addParam( const std::string& param, const std::string& value );
	virtual int									execute() const override;

};


NS_ARI_END