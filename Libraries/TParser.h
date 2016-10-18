#pragma once

#include <string>
#include "TSettingsItem.h"
#include "GlobalDefines.h"

NS_CORE_START

class TParser
{
private:

	static const char							s_delimiter;

public:

	static TSettingsItem						parse( const std::string & str );
	static std::string							pack( const TSettingsItem & line );

};

NS_CORE_END