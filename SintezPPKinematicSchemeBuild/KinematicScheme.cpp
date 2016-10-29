#include "KinematicScheme.h"
#include <iostream>

NS_ARI_USING

NS_CORE ChainArray& KinematicScheme::operator[]( int xPos )
{
	return m_field[xPos / PlanetaryGearSet::s_xSize][ xPos % PlanetaryGearSet::s_xSize];
}

const NS_CORE ChainArray& KinematicScheme::operator[]( int xPos ) const
{
	return m_field[xPos / PlanetaryGearSet::s_xSize][xPos % PlanetaryGearSet::s_xSize];
}

void KinematicScheme::addGearSet( const PlanetaryGearSet & gearSet )
{
	m_field.emplace_back( gearSet );		
}

void KinematicScheme::addRoute( const TCordinatesArray & cord, const NS_CORE Link & link )
{
	for ( auto& it : cord )
	{
		( *this )[it.m_x][it.m_y].addLinkToChain(link);
		( *this )[it.m_x][it.m_y].addChainToChain( ( *this )[cord[0].m_x][cord[0].m_y] );
		( *this )[it.m_x][it.m_y].addChainToChain( ( *this )[cord[cord.size() - 1].m_x][cord[cord.size() - 1].m_y] );
	}
	for ( size_t x = 0; x < m_field.size() * PlanetaryGearSet::s_xSize; x++ )
	{
		for ( auto y = 0; y < PlanetaryGearSet::s_ySize; y++ )
		{
			//if ( ( *this )[x][y].find( link.getElem1( ) ) || ( *this )[x][y].find( link.getElem2( ) ) )
			if ( ( *this )[x][y].find( link.getElem1() ) || 
				( ( *this )[x][y].find( link.getElem2() ) && link.getElem2() != NS_CORE Element::BRAKE )  )
			{
				( *this )[x][y].addLinkToChain( link );
			}
		}
	}
	
}

void ari::KinematicScheme::addFakeRoute( const TCordinatesArray & cord, const NS_CORE Link & link )
{
	const int interval = 1;

	int b = interval;
	for ( auto& it : cord )
	{
		b++;
		if ( b == interval + 1 )
		{
			( *this )[it.m_x][it.m_y].addLinkToChain( link );
			( *this )[it.m_x][it.m_y].addChainToChain( ( *this )[cord[0].m_x][cord[0].m_y] );
			( *this )[it.m_x][it.m_y].addChainToChain( ( *this )[cord[cord.size() - 1].m_x][cord[cord.size() - 1].m_y] );
			b = 0;
		}
	}
	for ( size_t x = 0; x < m_field.size() * PlanetaryGearSet::s_xSize; x++ )
	{
		for ( auto y = 0; y < PlanetaryGearSet::s_ySize; y++ )
		{
			if ( ( *this )[x][y].find( link.getElem1() ) || 
				( ( *this )[x][y].find( link.getElem2() ) && link.getElem2() != NS_CORE Element::BRAKE ) )
			{
				( *this )[x][y].addLinkToChain( link );
			}
		}
	}
}

void KinematicScheme::addBorders()
{
	//top and bottoms borders
	for ( size_t x = 0; x < m_field.size() * PlanetaryGearSet::s_xSize; x++ )
	{
		m_field[x / PlanetaryGearSet::s_xSize][x%PlanetaryGearSet::s_xSize][0].addElementToChain( NS_CORE Element::EMPTY );
		m_field[x / PlanetaryGearSet::s_xSize][x%PlanetaryGearSet::s_xSize][PlanetaryGearSet::s_ySize - 1].addElementToChain( NS_CORE Element::EMPTY );
	}
	//brakes
	for ( size_t x = 1; x < m_field.size() * PlanetaryGearSet::s_xSize - 1; x++ )
	{
		m_field[x / PlanetaryGearSet::s_xSize][x%PlanetaryGearSet::s_xSize][PlanetaryGearSet::s_ySize - 2].addElementToChain( NS_CORE Element::BRAKE );
	}
	//left and right borders
	for ( auto y = 0; y < PlanetaryGearSet::s_ySize; y++ )
	{
		m_field[0][0][y].addElementToChain( NS_CORE Element::EMPTY );
		m_field[m_field.size() - 1][PlanetaryGearSet::s_xSize - 1][y].addElementToChain( NS_CORE Element::EMPTY );
	}
	//input-output
	m_field[0][1][1].addElementToChain( NS_CORE Element::INPUT );
	m_field[m_field.size() - 1][PlanetaryGearSet::s_xSize - 2][1].addElementToChain( NS_CORE Element::OUTPUT );
	//brakes
}

void KinematicScheme::print()
{
	for ( size_t xPos = 0; xPos < m_field.size(); xPos++ )
	{
		m_field[xPos].print( );
	}
}

void KinematicScheme::create( const NS_CORE Code& code, const NS_CORE InternalGearRatios & k )
 {
	m_code = code;
	m_k = k;
	//m_code.createChains();
 }

size_t KinematicScheme::size() const
{
	return PlanetaryGearSet::s_xSize * m_field.size();
}

NS_CORE KinematicSchemeData KinematicScheme::getKinemaricSchemeCharacteristics() const
{
	NS_CORE KinematicSchemeData result;
	const auto center = PlanetaryGearSet::s_centerX;

	int maxCount = 0;

	for ( size_t i = 0; i < m_field.size(); i++ )
	{
		auto elem = m_field[i][center][0];
		int count = 0;

		for ( size_t j = 1; j < m_field[i][center].size(); j++ )
		{
			if ( m_field[i][center][j] != elem && m_field[i][center][j].size() > 0 && m_field[i][center][j] != NS_CORE Chain(NS_CORE Element::EMPTY) )
			{
				elem = m_field[i][center][j];
				count++;
			}
		}

		if ( count > maxCount )
			maxCount = count;
	}

	result._radialRoads = maxCount;


	return result;
}
