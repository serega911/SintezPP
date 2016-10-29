#include "PlanetaryGearSet.h"
#include <iostream>

NS_ARI_USING

const int										PlanetaryGearSet::s_xSize = 11;
const int										PlanetaryGearSet::s_ySize = 17;
const int										PlanetaryGearSet::s_centerX = s_xSize / 2;
const int										PlanetaryGearSet::s_centerY = s_ySize / 2;

void PlanetaryGearSet::print()
{
	for ( size_t yPos = 0; yPos < m_field.size(); yPos++ )
	{
		printLine( yPos );
		std::cout << std::endl;
	}
}

void PlanetaryGearSet::printLine( int yPos )
{
	for ( size_t i = 0; i < m_field[yPos].size(); i++ )
	{
		if ( m_field[yPos][i].size( ) != 0 )
		{
			if ( m_field[yPos][i].find( core::Element::EMPTY ) )
				std::cout << '#';
			else if ( m_field[yPos][i].find( core::Element::BRAKE ) )
				std::cout << 'B';
			else if ( m_field[yPos][i].find( core::Element::INPUT ) )
				std::cout << 'I';
			else if ( m_field[yPos][i].find( core::Element::OUTPUT ) )
				std::cout << 'O';
			else
				std::cout << '%';
		}
		else
			std::cout << ' ';
	}
}

void PlanetaryGearSet::create( NS_CORE GearSetNumber gearSetN, Type type )
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
		case PlanetaryGearSet::Type::TYPE_N_REVERSE:
			reverseX();
			break;
		case PlanetaryGearSet::Type::TYPE_U:
			reverseY();
			break;
		case PlanetaryGearSet::Type::TYPE_U_REVERSE:
			reverseY();
			reverseX();
			break;
		}
	}
}

const NS_CORE ChainArray& PlanetaryGearSet::operator[]( int xPos ) const
{
	return m_field[xPos];
}

NS_CORE ChainArray& PlanetaryGearSet::operator[]( int xPos )
{
	return m_field[xPos];
}

void PlanetaryGearSet::resetField()
{
	m_field.resize( s_xSize );
	for ( auto & line : m_field )
	{
		line.resize( s_ySize );
		for ( auto & elem : line )
			elem.clear( );
	}
}

void PlanetaryGearSet::createTypeN( NS_CORE GearSetNumber gearSetN )
{
	for ( auto y = s_centerY - 1; y < s_centerY + 2; y++ )
	{
		m_field[s_centerX + 1][y].addElementToChain( core::Element::EMPTY );
		m_field[s_centerX - 1][y].addElementToChain( core::Element::EMPTY );
	}
	for ( auto x = s_centerX - 1; x < s_centerX + 2; x++ )
	{
		m_field[x][s_centerY + 2].addElementToChain( core::Element( core::eMainElement::CARRIER, gearSetN ) );
	}
	m_field[s_centerX - 1][s_centerY - 2].addElementToChain( core::Element( core::eMainElement::SUN_GEAR, gearSetN ) );
	m_field[s_centerX + 1][s_centerY - 2].addElementToChain( core::Element( core::eMainElement::EPICYCLIC_GEAR, gearSetN ) );
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

void PlanetaryGearSet::createTypeDefault( NS_CORE GearSetNumber gearSetN )
{
	m_field[s_centerX][s_centerY + 2].addElementToChain( core::Element( core::eMainElement::EPICYCLIC_GEAR, gearSetN ) );
	m_field[s_centerX][s_centerY + 1].addElementToChain( core::Element::EMPTY );
	for ( auto x = s_centerX - 1; x < s_centerX + 2; x++ )
	{
		m_field[x][s_centerY].addElementToChain( core::Element( core::eMainElement::CARRIER, gearSetN ) );
	}				 
	m_field[s_centerX][s_centerY - 1].addElementToChain( core::Element::EMPTY );
	m_field[s_centerX][s_centerY - 2].addElementToChain( core::Element( core::eMainElement::SUN_GEAR, gearSetN ) );
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



void PlanetaryGearSet::reverseX()
{
	for ( size_t x = 0; x < m_field.size() / 2; x++ )
	{
		std::swap( m_field[x], m_field[m_field.size() - 1 - x] );
	}
}

void PlanetaryGearSet::reverseY()
{
	for ( size_t x = 0; x < m_field.size(); x++ )
		for ( size_t y = 0; y < m_field[x].size() / 2; y++ )
		{
			std::swap( m_field[x][y], m_field[x][m_field[x].size() - 1 - y] );
		}
}
