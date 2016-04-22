#include "TPlanetaryGearSet.h"

const int										pss::TPlanetaryGearSet::s_maxX = 9;
const int										pss::TPlanetaryGearSet::s_maxY = 13;
const int										pss::TPlanetaryGearSet::s_centerX = s_maxX / 2;
const int										pss::TPlanetaryGearSet::s_centerY = s_maxY / 2;

void pss::TPlanetaryGearSet::makeLimits( Type type )
{
	switch ( type )
	{
	case pss::TPlanetaryGearSet::Type::TYPE_N:
		makeLimitsForTypeN();
		break;
	case pss::TPlanetaryGearSet::Type::TYPE_N_REVERSE:
		makeLimitsForTypeNReverse();
		break;
	case pss::TPlanetaryGearSet::Type::TYPE_U:
		makeLimitsForTypeU();
		break;
	case pss::TPlanetaryGearSet::Type::TYPE_U_REVERSE:
		makeLimitsForTypeUReverse();
		break;
	case pss::TPlanetaryGearSet::Type::TYPE_DEFAULT:
		makeLimitsForTypeDefault();
		break;
	}
}

pss::TPlanetaryGearSet::TPlanetaryGearSet()
{
	const size_t mas_size = 6;
	m_fieldWithLimts.resize( mas_size );
	for ( size_t i = 0; i < mas_size; i++ )
	{
		m_fieldWithLimts[i].resize( s_maxY );
		for ( size_t j = 0; j < s_maxY; j++ )
			m_fieldWithLimts[i][j].resize( s_maxX );
	}
	m_planetaryGearSetType = Type::TYPE_DEFAULT;
	makeLimits( Type::TYPE_DEFAULT );
}

pss::TPlanetaryGearSet::~TPlanetaryGearSet()
{
}

void pss::TPlanetaryGearSet::create( int gearSetN, Type type )
{
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

	if ( type != m_planetaryGearSetType )
		makeLimits( type );

	invers();

	m_planetaryGearSetType = type;
}

void pss::TPlanetaryGearSet::invers()
{
	for ( auto & it : m_fieldWithLimts )
	{
		for ( int i = 0; i < it.size(); i++ )
		{
			if ( m_field[i].size() != 0 )
				it[i] = m_field[i];
		}
	}
}

void pss::TPlanetaryGearSet::resetField()
{
	m_field.resize( s_maxY );
	for ( auto & line : m_field )
	{
		line.resize( s_maxX );
		for ( auto & elem : line )
			elem.clear( );
	}
}

void pss::TPlanetaryGearSet::resetLimits()
{
	for ( auto& field : m_fieldWithLimts )
	{
		field.resize( s_maxY );
		for ( auto & line : field )
		{
			line.resize( s_maxX );
			for ( auto & elem : line )
				elem.clear();
		}
	}
}

void pss::TPlanetaryGearSet::makeLimitsForTypeN()
{
	for ( size_t i = s_centerX + 2; i < s_maxX; i++ )
	{
		m_fieldWithLimts[0][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[1][i][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[4][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[5][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 1; i < s_centerX - 2; i++ )
	{
		m_fieldWithLimts[2][i][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[3][i][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 2; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[3][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	m_fieldWithLimts[2][s_centerX - 2][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[2][s_centerX - 3][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[3][s_centerX - 2][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[3][s_centerX - 3][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
}

void pss::TPlanetaryGearSet::makeLimitsForTypeNReverse()
{
	for ( size_t i = s_centerX + 2; i < s_maxX; i++ )
	{
		m_fieldWithLimts[0][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[1][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[4][i][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[5][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 1; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[2][i][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[3][i][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 2; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[3][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	m_fieldWithLimts[2][( s_centerX - 2 )][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[2][( s_centerX - 3 )][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[3][( s_centerX - 2 )][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[3][( s_centerX - 3 )][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
}

void pss::TPlanetaryGearSet::makeLimitsForTypeU()
{
	for ( size_t i = 1; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[0][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[1][i][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[4][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[5][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 2; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[1][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 2; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[4][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = s_centerX + 2; i < s_maxX; i++ )
	{
		m_fieldWithLimts[2][i][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[3][i][1 + s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	m_fieldWithLimts[2][s_centerX + 2][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[2][s_centerX + 3][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[3][s_centerX + 2][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[3][s_centerX + 3][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
}

void pss::TPlanetaryGearSet::makeLimitsForTypeUReverse()
{
	for ( size_t i = 1; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[0][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[1][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[4][i][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[5][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 2; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[1][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 2; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[4][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = s_centerX + 2; i < s_maxX; i++ )
	{
		m_fieldWithLimts[2][i][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[3][i][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	m_fieldWithLimts[2][( s_centerX + 2 )][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[2][( s_centerX + 3 )][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[3][( s_centerX + 2 )][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
	m_fieldWithLimts[3][( s_centerX + 3 )][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
}

void pss::TPlanetaryGearSet::makeLimitsForTypeDefault()
{
	for ( size_t i = 1; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[0][i][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[1][i][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 2; i < s_centerX - 1; i++ )
	{
		m_fieldWithLimts[1][i][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = s_centerX - 1; i < s_centerX + 2; i++ ){
		if ( i != s_centerX )
		{
			m_fieldWithLimts[2][i][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );
			m_fieldWithLimts[3][i][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );
		}
		m_fieldWithLimts[2][i][s_centerY - 2].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[3][i][s_centerY + 2].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = s_centerX + 2; i < s_maxX; i++ )
	{
		m_fieldWithLimts[4][i][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );
		m_fieldWithLimts[5][i][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	for ( size_t i = 2; i < s_centerX - 2; i++ )
	{
		m_fieldWithLimts[5][i][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );
	}
}

void pss::TPlanetaryGearSet::createTypeN( int gearSetN )
{
	m_field[s_centerX + 2][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );			// # # # # # # # # #
	m_field[s_centerX + 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
	m_field[s_centerX][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
																																									// . . . 3 3 3 . . . 
	m_field[s_centerX + 2][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );	// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . # . # . . . 
	m_field[s_centerX][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . # . # . . . 
	m_field[s_centerX - 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . 1 . 2 . . . 
																																									// . . . . . . . . .	
	m_field[s_centerX - 2][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// . . . . . . . . .
	m_field[s_centerX - 2][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX - 2][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// # # # # # # # # #
}

void pss::TPlanetaryGearSet::createTypeNReverse( int gearSetN )
{
	m_field[s_centerX + 2][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );	// # # # # # # # # #
	m_field[s_centerX + 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
	m_field[s_centerX][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . . . . . .
	m_field[s_centerX - 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
																																									// . . . 3 3 3 . . . 
	m_field[s_centerX + 2][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );			// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . # . # . . . 
	m_field[s_centerX][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . # . # . . . 
	m_field[s_centerX - 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . 2 . 1 . . . 
																																									// . . . . . . . . .	
	m_field[s_centerX - 2][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// . . . . . . . . .
	m_field[s_centerX - 2][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX - 2][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// # # # # # # # # #
}

void pss::TPlanetaryGearSet::createTypeU( int gearSetN )
{
	m_field[s_centerX - 2][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );			// # # # # # # # # #
	m_field[s_centerX - 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
	m_field[s_centerX][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . . . . . .
	m_field[s_centerX + 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
																																									// . . . 1 . 2 . . . 
	m_field[s_centerX - 2][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );	// . . . # . # . . . 
	m_field[s_centerX - 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . # . # . . . 
	m_field[s_centerX][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . 3 3 3 . . . 
																																									// . . . . . . . . .	
	m_field[s_centerX + 2][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// . . . . . . . . .
	m_field[s_centerX + 2][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX + 2][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// # # # # # # # # #
}

void pss::TPlanetaryGearSet::createTypeUReverse( int gearSetN )
{
	m_field[s_centerX - 2][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );	// # # # # # # # # #
	m_field[s_centerX - 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
	m_field[s_centerX][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . . . . . .
	m_field[s_centerX + 1][s_centerY - 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . . . . . . .
																																									// . . . 2 . 1 . . .
	m_field[s_centerX - 2][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );			// . . . # . # . . . 
	m_field[s_centerX - 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . # . # . . . 
	m_field[s_centerX][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . # . # . . . 
	m_field[s_centerX + 1][s_centerY + 1].addElementToChain( pss::TElement::PLACEHOLDER );																			// . . . 3 3 3 . . . 
																																									// . . . . . . . . .
	m_field[s_centerX + 2][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// . . . . . . . . .
	m_field[s_centerX + 2][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[s_centerX + 2][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );			// # # # # # # # # #
}

void pss::TPlanetaryGearSet::createTypeDefault( int gearSetN )
{
	m_field[s_centerX - 2][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::EPICYCLIC_GEAR ), gearSetN ) );		// # # # # # # # # #	
	m_field[s_centerX - 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );;																				// . . . . . . . . .
	m_field[(s_centerX)][s_centerY - 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . . . . . .
	m_field[(s_centerX)][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );					// . . . . . . . . .
	m_field[(s_centerX)][s_centerY + 1].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::CARRIER ), gearSetN ) );				// . . . . 2 . . . . 
	m_field[s_centerX + 1][s_centerY].addElementToChain( pss::TElement::PLACEHOLDER );																				// . . . . 9 . . . . 
	m_field[s_centerX + 2][s_centerY].addElementToChain( pss::TElement( pss::TMainElement( pss::TMainElement::eMainElements::SUN_GEAR ), gearSetN ) );				// . . . 3 3 3 . . .
																																									// . . . . 9 . . . . 
																																									// . . . . 1 . . . . 
																																									// . . . . . . . . .
																																									// . . . . . . . . .
																																									// . . . . . . . . .
																																									// # # # # # # # # #
}
