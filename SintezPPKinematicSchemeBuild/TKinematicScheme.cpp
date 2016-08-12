#include "TKinematicScheme.h"
#include <iostream>

NS_ARI_USING

std::vector<core::TChain>& TKinematicScheme::operator[]( int xPos ) 
{
	return m_field[xPos / TPlanetaryGearSet::s_xSize][ xPos % TPlanetaryGearSet::s_xSize];
}

const std::vector<core::TChain>& TKinematicScheme::operator[]( int xPos ) const
{
	return m_field[xPos / TPlanetaryGearSet::s_xSize][xPos % TPlanetaryGearSet::s_xSize];
}

void TKinematicScheme::addGearSet( const TPlanetaryGearSet & gearSet )
{
	m_field.emplace_back( gearSet );		
}

void TKinematicScheme::addRoute( const std::vector<TCordinates> & cord, const core::TLink & link )
{
	for ( auto& it : cord )
	{
		( *this )[it.m_x][it.m_y].addLinkToChain(link);
		( *this )[it.m_x][it.m_y].addChainToChain( ( *this )[cord[0].m_x][cord[0].m_y] );
		( *this )[it.m_x][it.m_y].addChainToChain( ( *this )[cord[cord.size() - 1].m_x][cord[cord.size() - 1].m_y] );
	}
	for ( auto x = 0; x < m_field.size() * TPlanetaryGearSet::s_xSize; x++ )
	{
		for ( auto y = 0; y < TPlanetaryGearSet::s_ySize; y++ )
		{
			if ( ( *this )[x][y].find( link.getElem1( ) ) || ( *this )[x][y].find( link.getElem2( ) ) )
			{
				( *this )[x][y].addLinkToChain( link );
			}
		}
	}
	
}

void TKinematicScheme::addBorders()
{
	//top and bottoms borders
	for ( auto x = 0; x < m_field.size() * TPlanetaryGearSet::s_xSize; x++ )
	{
		m_field[x / TPlanetaryGearSet::s_xSize][x%TPlanetaryGearSet::s_xSize][0].addElementToChain( core::TElement::EMPTY );
		m_field[x / TPlanetaryGearSet::s_xSize][x%TPlanetaryGearSet::s_xSize][TPlanetaryGearSet::s_ySize - 1].addElementToChain( core::TElement::EMPTY );
	}
	//brakes
	for ( auto x = 1; x < m_field.size() * TPlanetaryGearSet::s_xSize - 1; x++ )
	{
		m_field[x / TPlanetaryGearSet::s_xSize][x%TPlanetaryGearSet::s_xSize][TPlanetaryGearSet::s_ySize - 2].addElementToChain( core::TElement::BRAKE );
	}
	//left and right borders
	for ( auto y = 0; y < TPlanetaryGearSet::s_ySize; y++ )
	{
		m_field[0][0][y].addElementToChain( core::TElement::EMPTY );
		m_field[m_field.size() - 1][TPlanetaryGearSet::s_xSize - 1][y].addElementToChain( core::TElement::EMPTY );
	}
	//input-output
	m_field[0][1][1].addElementToChain( core::TElement::INPUT );
	m_field[m_field.size() - 1][TPlanetaryGearSet::s_xSize - 2][1].addElementToChain( core::TElement::OUTPUT );
	//brakes
}

void TKinematicScheme::print()
{
	for ( auto xPos = 0; xPos < m_field.size(); xPos++ )
	{
		m_field[xPos].print( );
	}
}

void TKinematicScheme::create( const core::TCode& code, core::TK & k )
{
	m_code = code;
	m_k = k;
	//m_code.createChains();
}

size_t TKinematicScheme::size() const
{
	return TPlanetaryGearSet::s_xSize * m_field.size();
}
