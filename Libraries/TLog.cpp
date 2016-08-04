#include <iostream>

#include "TLog.h"

NS_CORE_USING

void TLog::log( const std::string& message, const bool isEndlNedded /*= true */ )
{
	std::cout << message;
	if ( isEndlNedded )
	{
		std::cout <<  std::endl;
	}
}

void TLog::warning( const bool condition, const std::string& message, eWarningImportance importance, const std::string& senderName )
{
	if ( condition )
	{
		std::cout << senderName << " : " << message;
		system( "pause" );
		if ( eWarningImportance::CRITICAL == importance )
		{
			std::cout << "This is a critical exception. The Programm wil be aborted.\n";
			system( "pause" );
			exit( 0 );
		}
		else if ( eWarningImportance::NON_CRITICAL == importance )
		{
			system( "pause" );
		}
	}
}

