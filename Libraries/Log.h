#pragma once

#include <string>
#include <iostream>

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

	enum eColor
	{
		BLACK
		,WHITE
		,RED
		,GREEN
		,BLUE
		,YELLOW
	};

	template<class T>
	static void log( const T& message, const bool isEndlNedded = true, const eColor font = WHITE, const eColor back = BLACK )
	{
		bool change = false;
		if ( back != s_defaultBackColor || font != s_defaultFontColor )
			change = true;

		if (change)
			SetColor( back, font );

		std::cout << message;
		
		if ( change )
			SetColor( s_defaultBackColor, s_defaultFontColor );

		if ( isEndlNedded )
		{
			std::cout << std::endl;
		}
	}

	static void									warning( const bool condition, const std::string& message, eWarningImportance importance,  const std::string& senderName = "Unknown" );

private:

	static const eColor							s_defaultFontColor;
	static const eColor							s_defaultBackColor;

	static int getColorNum( const eColor color );
	static void	SetColor( const eColor background, const eColor text );
};

NS_CORE_END
