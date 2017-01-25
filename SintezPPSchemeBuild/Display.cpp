#include <windows.h>
#include <iostream>
#include "../Libraries/Log.h"

#include "Display.h"

NS_ARI_USING


void ari::Display::cursorPositionSet( const Cordinate & cord ) const
{
	static HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD position = { cord.m_x, cord.m_y };
	SetConsoleCursorPosition( hConsole, position );
}

void ari::Display::print( const Cordinate& cord, const char c ) const
{
	cursorPositionSet( cord );
	NS_CORE Log::log( c, false, m_fontColor, m_backColor );
}

ari::Display_p ari::Display::create()
{
	return Display_p( new Display );
}

void ari::Display::setColors( NS_CORE eColor font, NS_CORE eColor background )
{
	m_fontColor = font;
	m_backColor = background;
}

void ari::Display::resetColors()
{
	setColors( NS_CORE eColor::WHITE, NS_CORE eColor::BLACK );
}

ari::Display::Display()
{
	resetColors();
}

void ari::Display::printLink( const ISchemeElement_p element ) const
{
	const auto& cords = element->getCordsWorldSpace();

	for ( const auto& it : cords )
	{
		char c;

		if ( it->isConsist( NS_CORE Element::INPUT ) )
			c = 'I';
		else if ( it->isConsist( NS_CORE Element::OUTPUT ) )
			c = 'O';
		else if ( it->isConsist( NS_CORE Element::BRAKE ) )
			c = 'B';
		else
			c = '#';

		print( it->getCord(), c );
	}
}

void ari::Display::printStatic( const ISchemeElement_p element ) const
{
	printLink( element );
}

