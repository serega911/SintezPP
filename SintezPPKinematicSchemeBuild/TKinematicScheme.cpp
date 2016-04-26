#include "TKinematicScheme.h"
#include <iostream>


std::vector<pss::TChain>& pss::TKinematicScheme::operator[]( int xPos ) 
{
	return m_field[xPos / TPlanetaryGearSet::s_xSize][ xPos % TPlanetaryGearSet::s_xSize];
}

const std::vector<pss::TChain>& pss::TKinematicScheme::operator[]( int xPos ) const
{
	return m_field[xPos / TPlanetaryGearSet::s_xSize][xPos % TPlanetaryGearSet::s_xSize];
}

void pss::TKinematicScheme::addGearSet( const TPlanetaryGearSet & gearSet )
{
	m_field.emplace_back( gearSet );		
}

void pss::TKinematicScheme::addBorders()
{
	//input-output-brakes
	for ( auto x = 0; x < m_field.size() * pss::TPlanetaryGearSet::s_xSize; x++ )
	{
		//input-output
		auto & chain = m_field[x / pss::TPlanetaryGearSet::s_xSize][x%pss::TPlanetaryGearSet::s_xSize][0];
		chain.clear();
		if ( x < m_field.size() * pss::TPlanetaryGearSet::s_xSize / 2 )
			chain.addElementToChain( pss::TElement::INPUT );
		else
			chain.addElementToChain( pss::TElement::OUTPUT );
		//brakes
		auto & brakeChain = m_field[x / pss::TPlanetaryGearSet::s_xSize][x%pss::TPlanetaryGearSet::s_xSize][pss::TPlanetaryGearSet::s_ySize - 1];
		brakeChain.addElementToChain( pss::TElement::BRAKE );
	}
	//left and right borders
	for ( auto y = 0; y < pss::TPlanetaryGearSet::s_ySize; y++ )
	{
		auto & leftBorder = m_field[0][0][y];
		leftBorder.addElementToChain( pss::TElement::BRAKE );
		auto & rightBorder = m_field[m_field.size( ) - 1][pss::TPlanetaryGearSet::s_xSize - 1][y];
		rightBorder.addElementToChain( pss::TElement::BRAKE );
	}
}

void pss::TKinematicScheme::print()
{
	for ( auto xPos = 0; xPos < m_field.size(); xPos++ )
	{
		m_field[xPos].print( );
	}
}

void pss::TKinematicScheme::create( const pss::TCode& code, pss::TK & k )
{
	m_code = code;
	m_k = k;
	m_code.createChains();
}

size_t pss::TKinematicScheme::size() const
{
	return TPlanetaryGearSet::s_xSize * m_field.size();
}
