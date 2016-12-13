#include <Windows.h>

#include "Log.h"

NS_CORE_USING

const core::Log::eColor core::Log::s_defaultBackColor = BLACK;
const core::Log::eColor core::Log::s_defaultFontColor = WHITE;

void Log::warning( const bool condition, const std::string& message, eWarningImportance importance, const std::string& senderName )
{
	if ( condition )
	{
		std::cout << std::endl << senderName << " : " << message << std::endl;
		if ( eWarningImportance::CRITICAL == importance )
		{
			std::cout << "This is a critical exception. The Programm wil be aborted.\n";
			system( "pause" );
			exit( 0 );
		}
	}
}


int Log::getColorNum( const eColor color )
{
	switch ( color )
	{
	case BLACK: return 0; break;
	case WHITE: return 15; break;
	case RED: return 4; break;
	case GREEN: return 2; break;
	case BLUE: return 1; break;
	case YELLOW: return 6; break;
	}
}

void Log::SetColor( const eColor background, const eColor text )
{
		HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hStdOut, (WORD)( ( getColorNum( background ) << 4 ) | getColorNum( text ) ) );
}