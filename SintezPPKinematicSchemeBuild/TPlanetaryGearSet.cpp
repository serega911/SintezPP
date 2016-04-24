#include "TPlanetaryGearSet.h"
#include <iostream>

const int										pss::TPlanetaryGearSet::s_xSize = 9;
const int										pss::TPlanetaryGearSet::s_ySize = 13;
const int										pss::TPlanetaryGearSet::s_centerX = s_xSize / 2;
const int										pss::TPlanetaryGearSet::s_centerY = s_ySize / 2;

void pss::TPlanetaryGearSet::print()
{
	for ( auto yPos = 0; yPos < m_field.size( ); yPos++ )
	{
		printLine( yPos );
		std::cout << std::endl;
	}
}

void pss::TPlanetaryGearSet::printLine( int yPos )
{
	for ( auto i = 0; i < m_field[yPos].size(); i++ )
	{
		if ( m_field[yPos][i].size( ) != 0 )
		{
			if ( m_field[yPos][i].find( pss::TElement::PLACEHOLDER ) )
				std::cout << '#';
			else if ( m_field[yPos][i].find( pss::TElement::BRAKE ) )
				std::cout << 'B';
			else if( m_field[yPos][i].find( pss::TElement::INPUT ) )
				std::cout << 'I';
			else if( m_field[yPos][i].find( pss::TElement::OUTPUT ) )
				std::cout << 'O';
			else
				std::cout << '%';
		}
		else
			std::cout << '.';
	}
}

void pss::TPlanetaryGearSet::create( int gearSetN, Type type )
{
	m_gearSetN = gearSetN;
	resetField();

	switch ( type )
	{
	case pss::TPlanetaryGearSet::Type::TYPE_N:
		createTypeN( gearSetN );
		break;
	case pss::TPlanetaryGearSet::Type::TYPE_N_REVERSE:
		createTypeNReverse( gearSetN );
		break;
	case pss::TPlanetaryGearSet::Type::TYPE_U:
		createTypeU( gearSetN );
		break;
	case pss::TPlanetaryGearSet::Type::TYPE_U_REVERSE:
		createTypeUReverse( gearSetN );
		break;
	case pss::TPlanetaryGearSet::Type::TYPE_DEFAULT:
		createTypeDefault( gearSetN );
		break;
	}
	for ( int i = 0; i < s_xSize; i++ )
		m_field[i][s_ySize - 1].addElementToChain( pss::TElement::BRAKE );
}

std::vector<pss::TChain>& pss::TPlanetaryGearSet::operator[]( int xPos )
{
	return m_field[xPos];
}

void pss::TPlanetaryGearSet::resetField()
{
	m_field.resize( s_xSize );
	for ( auto & line : m_field )
	{
		line.resize( s_ySize );
		for ( auto & elem : line )
			elem.clear( );
	}
}

//
// All coments were rotated underclockwise
//

void pss::TPlanetaryGearSet::createTypeN( int gearSetN )
{
	m_field[s_centerX - 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );			// # # # # # # # # #
	m_field[s_centerX - 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
																																									// . . . 3 3 3 . . . 
	m_field[s_centerX + 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );	// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . 1 . 2 . . . 
																																									// . . . . . . . . .	
	m_field[s_centerX - 1][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// . . . . . . . . .
	m_field[s_centerX][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX + 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// # # # # # # # # #
}

void pss::TPlanetaryGearSet::createTypeNReverse( int gearSetN )
{
	m_field[s_centerX - 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );	// # # # # # # # # #
	m_field[s_centerX - 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
																																									// . . . 3 3 3 . . . 
	m_field[s_centerX + 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );			// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . 2 . 1 . . . 
																																									// . . . . . . . . .	
	m_field[s_centerX - 1][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// . . . . . . . . .
	m_field[s_centerX][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX + 1][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// # # # # # # # # #
}

void pss::TPlanetaryGearSet::createTypeU( int gearSetN )
{
	m_field[s_centerX - 1][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );			// # # # # # # # # #
	m_field[s_centerX - 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . . . . . .
	m_field[s_centerX - 1][s_centerX + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
																																									// . . . 1 . 2 . . . 
	m_field[s_centerX + 1][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );	// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . 3 3 3 . . . 
																																									// . . . . . . . . .	
	m_field[s_centerX - 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// . . . . . . . . .
	m_field[s_centerX][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX + 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// # # # # # # # # #
}

void pss::TPlanetaryGearSet::createTypeUReverse( int gearSetN )
{
	m_field[s_centerX - 1][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );	// # # # # # # # # #
	m_field[s_centerX - 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
																																									// . . . 2 . 1 . . .
	m_field[s_centerX + 1][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );			// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . 3 3 3 . . . 
																																									// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// . . . . . . . . .
	m_field[s_centerX][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX + 1][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// # # # # # # # # #
}

void pss::TPlanetaryGearSet::createTypeDefault( int gearSetN )
{
	m_field[s_centerX][s_centerY + 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );		// # # # # # # # # #	
	m_field[s_centerX][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );;																				// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );					// . . . . . . . . .
	m_field[s_centerX + 1][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . 2 . . . . 
	m_field[s_centerX][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . 9 . . . . 
	m_field[s_centerX][s_centerY - 2].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );				// . . . 3 3 3 . . .
																																									// . . . . 9 . . . . 
																																									// . . . . 1 . . . . 
																																									// . . . . . . . . .
																																									// . . . . . . . . .
																																									// . . . . . . . . .
																																									// # # # # # # # # #
}
