#pragma once

#include <string>
#include "SettingsItem.h"
#include "GlobalDefines.h"

NS_CORE_START

class Parser
{
private:

	static const char							s_delimiter;

public:

	static SettingsItem							parse( const std::string & str );
	static std::string							pack( const SettingsItem & line );

};

NS_CORE_END