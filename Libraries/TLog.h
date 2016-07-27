#pragma once

#include "../Libraries/GlobalDefines.h"
#include <string>

NS_PSS_START

class TLog
{
public:

	enum eWarningImportance
	{
		NON_CRITICAL
		,CRITICAL
	};

	static void									log( const std::string& message, const bool isEndlNedded = true );

	static void									warning( const bool condition, const std::string& message, eWarningImportance importance,  const std::string& senderName = "Unknown" );


};

NS_PSS_END