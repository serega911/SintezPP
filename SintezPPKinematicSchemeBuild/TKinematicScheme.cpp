#include "TKinematicScheme.h"
#include <iostream>


std::vector<pss::TChain>& pss::TKinematicScheme::operator[]( int xPos )
{
	return m_field[xPos / TPlanetaryGearSet::s_xSize][ xPos % TPlanetaryGearSet::s_xSize];
}

void pss::TKinematicScheme::addGearSet( const TPlanetaryGearSet & gearSet )
{
	m_field.emplace_back( gearSet );
// 	for ( auto x = 0; x < m_field.size() * pss::TPlanetaryGearSet::s_xSize; x++ )
// 	{
// 		auto & chain = getChainInCell( x, pss::TPlanetaryGearSet::s_ySize - 1 );
// 		chain.clear();
// 		if ( x < m_field.size( ) * pss::TPlanetaryGearSet::s_xSize / 2 )
// 			chain.addElementToChain( pss::TElement::INPUT );
// 		else
// 			chain.addElementToChain( pss::TElement::OUTPUT );
// 	}
		
}

void pss::TKinematicScheme::print()
{
	for ( auto xPos = 0; xPos < m_field.size(); xPos++ )
	{
		m_field[xPos].print( );
	}
}
