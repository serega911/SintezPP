#include "TPlanetaryGearSet.h"
#include <iostream>

NS_ARI_USING

const int										TPlanetaryGearSet::s_xSize = 11;
const int										TPlanetaryGearSet::s_ySize = 17;
const int										TPlanetaryGearSet::s_centerX = s_xSize / 2;
const int										TPlanetaryGearSet::s_centerY = s_ySize / 2;

void TPlanetaryGearSet::print()
{
	for ( auto yPos = 0; yPos < m_field.size( ); yPos++ )
	{
		printLine( yPos );
		std::cout << std::endl;
	}
}

void TPlanetaryGearSet::printLine( int yPos )
{
	for ( auto i = 0; i < m_field[yPos].size(); i++ )
	{
		if ( m_field[yPos][i].size( ) != 0 )
		{
			if ( m_field[yPos][i].find( core::TElement::EMPTY ) )
				std::cout << '#';
			else if ( m_field[yPos][i].find( core::TElement::BRAKE ) )
				std::cout << 'B';
			else if ( m_field[yPos][i].find( core::TElement::INPUT ) )
				std::cout << 'I';
			else if ( m_field[yPos][i].find( core::TElement::OUTPUT ) )
				std::cout << 'O';
			else
				std::cout << '%';
		}
		else
			std::cout << ' ';
	}
}

void TPlanetaryGearSet::create( int gearSetN, Type type )
{
	m_gearSetN = gearSetN;
	resetField();

	if ( type == Type::TYPE_DEFAULT )
	{
		createTypeDefault( gearSetN );
	}
	else
	{
		createTypeN( gearSetN );
		switch ( type )
		{
		case TPlanetaryGearSet::Type::TYPE_N_REVERSE:
			reverseX();
			break;
		case TPlanetaryGearSet::Type::TYPE_U:
			reverseY();
			break;
		case TPlanetaryGearSet::Type::TYPE_U_REVERSE:
			reverseY();
			reverseX();
			break;
		}
	}
}

const std::vector<core::TChain>& TPlanetaryGearSet::operator[]( int xPos ) const
{
	return m_field[xPos];
}

std::vector<core::TChain>& TPlanetaryGearSet::operator[]( int xPos )
{
	return m_field[xPos];
}

void TPlanetaryGearSet::resetField()
{
	m_field.resize( s_xSize );
	for ( auto & line : m_field )
	{
		line.resize( s_ySize );
		for ( auto & elem : line )
			elem.clear( );
	}
}

void TPlanetaryGearSet::createTypeN( int gearSetN )
{
	for ( auto y = s_centerY - 1; y < s_centerY + 2; y++ )
	{
		m_field[s_centerX + 1][y].addElementToChain( core::TElement::EMPTY );
		m_field[s_centerX - 1][y].addElementToChain( core::TElement::EMPTY );
	}
	for ( auto x = s_centerX - 1; x < s_centerX + 2; x++ )
	{
		m_field[x][s_centerY + 2].addElementToChain( core::TElement( core::eMainElement::CARRIER, gearSetN ) );
	}
	m_field[s_centerX - 1][s_centerY - 2].addElementToChain( core::TElement( core::eMainElement::SUN_GEAR, gearSetN ) );
	m_field[s_centerX + 1][s_centerY - 2].addElementToChain( core::TElement( core::eMainElement::EPICYCLIC_GEAR, gearSetN ) );
	// # # # # # # # # #
	// . . . . . . . . .
	// . . . . . . . . .
	// . . . . . . . . .
	// . . . 3 3 3 . . . 
	// . . . # . # . . . 
	// . . . # . # . . . 
	// . . . # . # . . . 
	// . . . 1 . 2 . . . 
	// . . . . . . . . .	
	// . . . . . . . . .
	// . . . . . . . . .
	// # # # # # # # # #			->x	^y
}

void TPlanetaryGearSet::createTypeDefault( int gearSetN )
{
	m_field[s_centerX][s_centerY + 2].addElementToChain( core::TElement( core::eMainElement::EPICYCLIC_GEAR, gearSetN ) );
	m_field[s_centerX][s_centerY + 1].addElementToChain( core::TElement::EMPTY );
	for ( auto x = s_centerX - 1; x < s_centerX + 2; x++ )
	{
		m_field[x][s_centerY].addElementToChain( core::TElement( core::eMainElement::CARRIER, gearSetN ) );
	}				 
	m_field[s_centerX][s_centerY - 1].addElementToChain( core::TElement::EMPTY );
	m_field[s_centerX][s_centerY - 2].addElementToChain( core::TElement( core::eMainElement::SUN_GEAR, gearSetN ) );
	// # # # # # # # # #
	// . . . . . . . . .
	// . . . . . . . . .
	// . . . . . . . . .
	// . . . . 2 . . . .
	// . . . . 9 . . . .
	// . . . 3 3 3 . . .
	// . . . . 9 . . . .
	// . . . . 1 . . . .
	// . . . . . . . . .
	// . . . . . . . . .
	// . . . . . . . . .
	// # # # # # # # # #			->x	^y
}



void TPlanetaryGearSet::reverseX()
{
	for ( auto x = 0; x < m_field.size()/2; x++ )
	{
		std::swap( m_field[x], m_field[m_field.size() - 1 - x] );
	}
}

void TPlanetaryGearSet::reverseY()
{
	for ( auto x = 0; x < m_field.size(); x++ )
	for ( auto y = 0; y < m_field[x].size() / 2; y++ )
	{
		std::swap( m_field[x][y], m_field[x][m_field[x].size() - 1 - y] );
	}
}
