#pragma once

#include <string>
#include <iostream>

#include "GlobalDefines.h"
#include "eColor.h"



NS_CORE_START

#define HERE std::string(__FILE__) + ": " + __FUNCTION__ + " "  + std::to_string(__LINE__)

class Log
{
public:

	enum eWarningImportance
	{
		NON_CRITICAL
		, CRITICAL
	};



	template<class T>
	static void log( const T& message, const bool isEndlNedded = true, const eColor font = eColor::WHITE, const eColor back = eColor::BLACK )
	{
		bool change = false;
		if ( back != s_defaultBackColor || font != s_defaultFontColor )
			change = true;

		if ( change )
			SetColor( back, font );

		std::cout << message;

		if ( change )
			SetColor( s_defaultBackColor, s_defaultFontColor );

		if ( isEndlNedded )
		{
			std::cout << std::endl;
		}
	}

	template<class T>
	static void askForValue( const std::string& prompt, T& value )
	{
		const int promptWidth = 35;

		std::cout.width( promptWidth );
		std::cout << std::left << prompt;
		std::cin >> value;
	}

	template<class T>
	static void askFor2Value( const std::string& prompt, const std::string& val1comment, const std::string& val2comment, T& value1, T& value2 )
	{
		const int promptWidth = 35;

		std::cout.width( promptWidth );
		std::cout << std::left << prompt << std::endl;

		std::cout.width( promptWidth );
		std::cout << std::left << val1comment;
		std::cin >> value1;

		std::cout.width( promptWidth );
		std::cout << std::left << val2comment;
		std::cin >> value2;
	}

	template<class T>
	static void showValue( const std::string& prompt, const T& value )
	{
		const int promptWidth = 35;

		std::cout.width( promptWidth );
		std::cout << std::left << prompt;
		std::cout << value << std::endl;
	}

	template<class T>
	static void show2Value( const std::string& prompt, const std::string& delimiter, const T& value1, const T& value2 )
	{
		const int promptWidth = 35;

		std::cout.width( promptWidth );
		std::cout << std::left << prompt;
		std::cout << value1 << delimiter << value2 << std::endl;
	}

	static void									warning( const bool condition, const std::string& message, eWarningImportance importance, const std::string& senderName = "Unknown" );

private:

	static const eColor							s_defaultFontColor;
	static const eColor							s_defaultBackColor;

	static int getColorNum( const eColor color );
	static void	SetColor( const eColor background, const eColor text );
};

NS_CORE_END
