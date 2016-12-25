#pragma once

#include <string>

#include "TestGlue.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class Command
{
private:

	std::string									m_command;

public:

	Command( const std::string appName );

	void addParam( const std::string& param, const std::string& value );

	const std::string& get() const;
};


NS_ARI_END