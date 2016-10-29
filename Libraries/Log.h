#pragma once

#include <string>

#include "GlobalDefines.h"

NS_CORE_START

class Log
{
public:

	enum eWarningImportance
	{
		NON_CRITICAL
		,CRITICAL
	};

	template<class T>
	static void log( const T& message, const bool isEndlNedded = true )
	{
		std::cout << message;
		if ( isEndlNedded )
		{
			std::cout << std::endl;
		}
	}

	static void									warning( const bool condition, const std::string& message, eWarningImportance importance,  const std::string& senderName = "Unknown" );


};

NS_CORE_END
