#include <Windows.h>

#include "Log.h"

NS_CORE_USING

const eColor core::Log::s_defaultBackColor = eColor::BLACK;
const eColor core::Log::s_defaultFontColor = eColor::WHITE;

void Log::warning( const bool condition, const std::string& message, eWarningImportance importance, const std::string& senderName )
{
	if ( condition )
	{
		std::cout << std::endl << senderName << " : " << message << std::endl;
		if ( eWarningImportance::CRITICAL == importance )
		{
			std::cout << "This is a critical exception. The Programm will be aborted.\n";
			system( "pause" );
			exit( 0 );
		}
	}
}

int Log::getColorNum( const eColor color )
{
	/*switch ( color )
	{
	case eColor::BLACK: return 0; break;
	case eColor::WHITE: return 15; break;
	case eColor::RED: return 4; break;
	case eColor::GREEN: return 2; break;
	case eColor::BLUE: return 1; break;
	case eColor::YELLOW: return 6; break;
	}*/
	return int( color );
}

void Log::SetColor( const eColor background, const eColor text )
{
		HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hStdOut, (WORD)( ( getColorNum( background ) << 4 ) | getColorNum( text ) ) );
}