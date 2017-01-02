#include <windows.h>
#include <iostream>
#include "Display.h"

NS_ARI_USING

Display::Display()
{
}


Display::~Display()
{
}

void ari::Display::cursorPositionSet( const Cordinate & cord ) const
{
	static HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD position = { cord.m_x, -cord.m_y };
	SetConsoleCursorPosition( hConsole, position );
}

void ari::Display::print( const Cordinate& cord, const char c ) const
{
	cursorPositionSet( cord );
	std::cout << c;
}


