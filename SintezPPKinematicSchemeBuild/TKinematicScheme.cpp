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

void pss::TKinematicScheme::addRoute( const std::vector<pss::TCordinates> & cord, const pss::TLink & link )
{
	for ( auto& it : cord )
	{
		( *this )[it.m_x][it.m_y].addLinkToChain(link);
		( *this )[it.m_x][it.m_y].addChainToChain( ( *this )[cord[0].m_x][cord[0].m_y] );
		( *this )[it.m_x][it.m_y].addChainToChain( ( *this )[cord[cord.size() - 1].m_x][cord[cord.size() - 1].m_y] );
	}
	for ( auto x = 0; x < m_field.size() * pss::TPlanetaryGearSet::s_xSize; x++ )
	{
		for ( auto y = 0; y < pss::TPlanetaryGearSet::s_ySize; y++ )
		{
			if ( ( *this )[x][y].find( link.getElem1( ) ) || ( *this )[x][y].find( link.getElem2( ) ) )
			{
				( *this )[x][y].addLinkToChain( link );
			}
		}
	}
	
}

void pss::TKinematicScheme::addBorders()
{
	//top and bottoms borders
	for ( auto x = 0; x < m_field.size() * pss::TPlanetaryGearSet::s_xSize; x++ )
	{
		m_field[x / pss::TPlanetaryGearSet::s_xSize][x%pss::TPlanetaryGearSet::s_xSize][0].addElementToChain( pss::TElement::PLACEHOLDER );
		m_field[x / pss::TPlanetaryGearSet::s_xSize][x%pss::TPlanetaryGearSet::s_xSize][pss::TPlanetaryGearSet::s_ySize - 1].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	//brakes
	for ( auto x = 1; x < m_field.size() * pss::TPlanetaryGearSet::s_xSize - 1; x++ )
	{
		m_field[x / pss::TPlanetaryGearSet::s_xSize][x%pss::TPlanetaryGearSet::s_xSize][pss::TPlanetaryGearSet::s_ySize - 2].addElementToChain( pss::TElement::BRAKE );
	}
	//left and right borders
	for ( auto y = 0; y < pss::TPlanetaryGearSet::s_ySize; y++ )
	{
		m_field[0][0][y].addElementToChain( pss::TElement::PLACEHOLDER );
		m_field[m_field.size( ) - 1][pss::TPlanetaryGearSet::s_xSize - 1][y].addElementToChain( pss::TElement::PLACEHOLDER );
	}
	//input-output
	m_field[0][1][1].addElementToChain( pss::TElement::INPUT );
	m_field[m_field.size( ) - 1][pss::TPlanetaryGearSet::s_xSize - 2][1].addElementToChain( pss::TElement::OUTPUT );
	//brakes
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
