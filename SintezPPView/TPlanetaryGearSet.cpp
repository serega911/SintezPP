#include "TPlanetaryGearSet.h"

NS_ARI_USING

const size_t TPlanetaryGearSet::s_mapWidth = 13;
const size_t TPlanetaryGearSet::s_mapHeight = 9;
const NS_CORE TChain ari::TPlanetaryGearSet::s_emptyChain = NS_CORE TChain();


NS_ARI TPlanetaryGearSet::TPlanetaryGearSet( ePlanetarySetType t /*= DEFAULT*/ )
{
	m_limitType = t;
	const size_t mas_size = 7;
	m_map.resize( mas_size );
	for ( size_t i = 0; i < mas_size; i++ )
		m_map[i].resize( s_mapWidth*s_mapHeight );
	MakeLimits( m_limitType );
}

NS_ARI TPlanetaryGearSet::~TPlanetaryGearSet( void )
{

}

void NS_ARI TPlanetaryGearSet::Create( NS_CORE TGearSetNumber Num, ePlanetarySetType t /*= DEFAULT*/ )
{
	int YC = ( s_mapHeight - 1 ) / 2;
	int XC = ( s_mapWidth - 1 ) / 2;
	for ( size_t i = 0; i < m_map[0].size(); i++ )
		m_map[0][i] = s_emptyChain;

	NS_CORE TChain epicyclic( NS_CORE TElement( NS_CORE eMainElement::EPICYCLIC_GEAR, Num ) );
	NS_CORE TChain sun( NS_CORE TElement( NS_CORE eMainElement::SUN_GEAR, Num ) );
	NS_CORE TChain carrier( NS_CORE TElement( NS_CORE eMainElement::CARRIER, Num ) );
	NS_CORE TChain wall( NS_CORE TElement::EMPTY );

	switch ( t ){
	DEFAULT:
		m_map[0][( XC - 2 )*s_mapHeight + YC] = epicyclic;			// # # # # # # # # #	
		m_map[0][( XC - 1 )*s_mapHeight + YC] = wall;				// . . . . . . . . .
		m_map[0][(XC)*s_mapHeight + YC - 1] = carrier;				// . . . . . . . . .
		m_map[0][(XC)*s_mapHeight + YC] = carrier;					// . . . . . . . . .
		m_map[0][(XC)*s_mapHeight + YC + 1] = carrier;				// . . . . 2 . . . . 
		m_map[0][( XC + 1 )*s_mapHeight + YC] = wall;				// . . . . 9 . . . . 
		m_map[0][( XC + 2 )*s_mapHeight + YC] = sun;				// . . . 3 3 3 . . .
		if ( t != m_limitType )										// . . . . 9 . . . . 
			MakeLimits( t );										// . . . . 1 . . . . 
		break;														// . . . . . . . . .
																	// . . . . . . . . .
																	// . . . . . . . . .
																	// # # # # # # # # #
	case P_NORMAL:
		m_map[0][( XC + 2 )*s_mapHeight + YC - 1] = sun;			//# # # # # # # # #
		m_map[0][( XC + 1 )*s_mapHeight + YC - 1] = wall;			// . . . . . . . . .
		m_map[0][XC*s_mapHeight + YC - 1] = wall;					// . . . . . . . . .
		m_map[0][( XC - 1 )*s_mapHeight + YC - 1] = wall;			// . . . . . . . . .
																	//      3 3 3
		m_map[0][( XC + 2 )*s_mapHeight + YC + 1] = epicyclic;		//      #   #
		m_map[0][( XC + 1 )*s_mapHeight + YC + 1] = wall;			//      #   #
		m_map[0][XC*s_mapHeight + YC + 1] = wall;					//      #   #
		m_map[0][( XC - 1 )*s_mapHeight + YC + 1] = wall;			//      1   2
																	// . . . . . . . . .	
		m_map[0][( XC - 2 )*s_mapHeight + YC - 1] = carrier;		// . . . . . . . . .
		m_map[0][( XC - 2 )*s_mapHeight + YC] = carrier;			// . . . . . . . . .
		m_map[0][( XC - 2 )*s_mapHeight + YC + 1] = carrier;		//# # # # # # # # #
		if ( t != m_limitType )
			MakeLimits( t );
		break;
	case U_NORMAL:
		m_map[0][( XC - 2 )*s_mapHeight + YC - 1] = sun;			// # # # # # # # # #
		m_map[0][( XC - 1 )*s_mapHeight + YC - 1] = wall;			// . . . . . . . . .
		m_map[0][XC*s_mapHeight + YC - 1] = wall;					// . . . . . . . . .
		m_map[0][( XC + 1 )*s_mapHeight + YC - 1] = wall;			// . . . . . . . . .
																	// . . . 1 . 2 . . . 
		m_map[0][( XC - 2 )*s_mapHeight + YC + 1] = epicyclic;		// . . . # . # . . . 
		m_map[0][( XC - 1 )*s_mapHeight + YC + 1] = wall;			// . . . # . # . . . 
		m_map[0][XC*s_mapHeight + YC + 1] = wall;					// . . . # . # . . . 
		m_map[0][( XC + 1 )*s_mapHeight + YC + 1] = wall;			// . . . 3 3 3 . . . 
																	// . . . . . . . . .	
		m_map[0][( XC + 2 )*s_mapHeight + YC - 1] = carrier;		// . . . . . . . . .
		m_map[0][( XC + 2 )*s_mapHeight + YC] = carrier;			// . . . . . . . . .
		m_map[0][( XC + 2 )*s_mapHeight + YC + 1] = carrier;		// # # # # # # # # #
		if ( t != m_limitType )
			MakeLimits( t );
		break;
	case P_INVERSE:
		m_map[0][( XC + 2 )*s_mapHeight + YC - 1] = epicyclic;		// # # # # # # # # #
		m_map[0][( XC + 1 )*s_mapHeight + YC - 1] = wall;			// . . . . . . . . .
		m_map[0][XC*s_mapHeight + YC - 1] = wall;					// . . . . . . . . .
		m_map[0][( XC - 1 )*s_mapHeight + YC - 1] = wall;			// . . . . . . . . .
																	// . . . 3 3 3 . . . 
		m_map[0][( XC + 2 )*s_mapHeight + YC + 1] = sun;			// . . . # . # . . . 
		m_map[0][( XC + 1 )*s_mapHeight + YC + 1] = wall;			// . . . # . # . . . 
		m_map[0][XC*s_mapHeight + YC + 1] = wall;					// . . . # . # . . . 
		m_map[0][( XC - 1 )*s_mapHeight + YC + 1] = wall;			// . . . 2 . 1 . . . 
																	// . . . . . . . . .	
		m_map[0][( XC - 2 )*s_mapHeight + YC - 1] = carrier;		// . . . . . . . . .
		m_map[0][( XC - 2 )*s_mapHeight + YC] = carrier;			// . . . . . . . . .
		m_map[0][( XC - 2 )*s_mapHeight + YC + 1] = carrier;		// # # # # # # # # #
		if ( t != m_limitType )
			MakeLimits( t );
		break;
	case U_INVERSE:
		m_map[0][( XC - 2 )*s_mapHeight + YC - 1] = epicyclic;		// # # # # # # # # #
		m_map[0][( XC - 1 )*s_mapHeight + YC - 1] = wall;			// . . . . . . . . .
		m_map[0][XC*s_mapHeight + YC - 1] = wall;					// . . . . . . . . .
		m_map[0][( XC + 1 )*s_mapHeight + YC - 1] = wall;			// . . . . . . . . .
																	// . . . 2 . 1 . . .
		m_map[0][( XC - 2 )*s_mapHeight + YC + 1] = sun;			// . . . # . # . . . 
		m_map[0][( XC - 1 )*s_mapHeight + YC + 1] = wall;			// . . . # . # . . . 
		m_map[0][XC*s_mapHeight + YC + 1] = wall;					// . . . # . # . . . 
		m_map[0][( XC + 1 )*s_mapHeight + YC + 1] = wall;			// . . . 3 3 3 . . . 
																	// . . . . . . . . .
		m_map[0][( XC + 2 )*s_mapHeight + YC - 1] = carrier;		// . . . . . . . . .
		m_map[0][( XC + 2 )*s_mapHeight + YC] = carrier;			// . . . . . . . . .
		m_map[0][( XC + 2 )*s_mapHeight + YC + 1] = carrier;		// # # # # # # # # #
		if ( t != m_limitType )
			MakeLimits( t );
		break;
	}
	size_t MasSize = m_map.size();
	for ( size_t i = 1; i < MasSize; i++ )
		Invers( i );
}

void NS_ARI TPlanetaryGearSet::Invers( int Num )
{
	for ( size_t i = 0; i < s_mapWidth*s_mapHeight; i++ )
		if ( m_map[0][i].size() != 0 )
			m_map[Num][i] = m_map[0][i];
}

size_t NS_ARI TPlanetaryGearSet::getXMAX()
{
	return s_mapWidth;
}

size_t NS_ARI TPlanetaryGearSet::getYMAX()
{
	return s_mapHeight;
}

NS_CORE TChain NS_ARI TPlanetaryGearSet::getCellMas( size_t i, size_t j )
{
	if ( !( i < 0 ) && !( i >( m_map.size() - 1 ) ) && !( j < 0 ) && !( j >( m_map[i].size() - 1 ) ) )
		return m_map[i][j];
	else
	{
		//exception	
	}
}

std::vector<NS_CORE TChain> NS_ARI TPlanetaryGearSet::getMas( size_t i )
{
	return m_map[i];
}

void NS_ARI TPlanetaryGearSet::MakeLimits( ePlanetarySetType t )
{
	m_limitType = t;
	size_t YC = ( s_mapHeight - 1 ) / 2;
	size_t XC = ( s_mapWidth - 1 ) / 2;
	for ( size_t i = 1; i < m_map.size(); i++ )
		for ( size_t j = 0; j < m_map[i].size(); j++ )
			m_map[i][j] = s_emptyChain;

	NS_CORE TChain wall( NS_CORE TElement::EMPTY );

	switch ( m_limitType ){
	DEFAULT:
		for ( size_t i = 1; i < XC - 1; i++ ){
			m_map[1][i*s_mapHeight - 1 + YC] = wall;
			m_map[2][i*s_mapHeight + 1 + YC] = wall;
		}
		for ( size_t i = 2; i < XC - 1; i++ ){
			m_map[2][i*s_mapHeight + YC - 1] = wall;
		}
		for ( size_t i = XC - 1; i < XC + 2; i++ ){
			if ( i != XC ){
				m_map[3][i*s_mapHeight - 1 + YC] = wall;
				m_map[4][i*s_mapHeight + 1 + YC] = wall;
			}
			m_map[3][i*s_mapHeight - 2 + YC] = wall;
			m_map[4][i*s_mapHeight + 2 + YC] = wall;
		}
		for ( size_t i = XC + 2; i < s_mapWidth; i++ ){
			m_map[5][i*s_mapHeight + 1 + YC] = wall;
			m_map[6][i*s_mapHeight - 1 + YC] = wall;
		}
		for ( size_t i = 2; i < XC - 2; i++ ){
			m_map[6][i*s_mapHeight + YC] = wall;
		}
		break;
	case P_NORMAL:
		for ( size_t i = XC + 2; i < s_mapWidth; i++ ){
			m_map[1][i*s_mapHeight + YC] = wall;
			m_map[2][i*s_mapHeight + YC + 2] = wall;
			m_map[5][i*s_mapHeight + YC] = wall;
			m_map[6][i*s_mapHeight + YC - 2] = wall;
		}
		for ( size_t i = 1; i < XC - 2; i++ ){
			m_map[3][i*s_mapHeight - 1 + YC] = wall;
			m_map[4][i*s_mapHeight + 1 + YC] = wall;
		}
		for ( size_t i = 2; i < XC - 1; i++ ){
			m_map[4][i*s_mapHeight + YC - 2] = wall;
		}
		m_map[3][( XC - 2 )*s_mapHeight - 2 + YC] = wall;
		m_map[3][( XC - 3 )*s_mapHeight - 2 + YC] = wall;
		m_map[4][( XC - 2 )*s_mapHeight + 2 + YC] = wall;
		m_map[4][( XC - 3 )*s_mapHeight + 2 + YC] = wall;
		break;
	case U_NORMAL:
		for ( size_t i = 1; i < XC - 1; i++ ){
			m_map[1][i*s_mapHeight + YC] = wall;
			m_map[2][i*s_mapHeight + YC + 2] = wall;
			m_map[5][i*s_mapHeight + YC] = wall;
			m_map[6][i*s_mapHeight + YC - 2] = wall;
		}
		for ( size_t i = 2; i < XC - 1; i++ ){
			m_map[2][i*s_mapHeight + YC] = wall;
		}
		for ( size_t i = 2; i < XC - 1; i++ ){
			m_map[5][i*s_mapHeight + YC - 2] = wall;
		}
		for ( size_t i = XC + 2; i < s_mapWidth; i++ ){
			m_map[3][i*s_mapHeight - 1 + YC] = wall;
			m_map[4][i*s_mapHeight + 1 + YC] = wall;
		}
		m_map[3][( XC + 2 )*s_mapHeight - 2 + YC] = wall;
		m_map[3][( XC + 3 )*s_mapHeight - 2 + YC] = wall;
		m_map[4][( XC + 2 )*s_mapHeight + 2 + YC] = wall;
		m_map[4][( XC + 3 )*s_mapHeight + 2 + YC] = wall;
		break;
	case P_INVERSE:
		for ( size_t i = XC + 2; i < s_mapWidth; i++ ){
			m_map[1][i*s_mapHeight + YC - 2] = wall;
			m_map[2][i*s_mapHeight + YC] = wall;
			m_map[5][i*s_mapHeight + YC + 2] = wall;
			m_map[6][i*s_mapHeight + YC] = wall;
		}
		for ( size_t i = 1; i < XC - 1; i++ ){
			m_map[3][i*s_mapHeight - 1 + YC] = wall;
			m_map[4][i*s_mapHeight + 1 + YC] = wall;
		}
		for ( size_t i = 2; i < XC - 1; i++ ){
			m_map[4][i*s_mapHeight + YC - 2] = wall;
		}
		m_map[3][( XC - 2 )*s_mapHeight - 2 + YC] = wall;
		m_map[3][( XC - 3 )*s_mapHeight - 2 + YC] = wall;
		m_map[4][( XC - 2 )*s_mapHeight + 2 + YC] = wall;
		m_map[4][( XC - 3 )*s_mapHeight + 2 + YC] = wall;
		break;
	case U_INVERSE:
		for ( size_t i = 1; i < XC - 1; i++ ){
			m_map[1][i*s_mapHeight + YC - 2] = wall;
			m_map[2][i*s_mapHeight + YC] = wall;
			m_map[5][i*s_mapHeight + YC + 2] = wall;
			m_map[6][i*s_mapHeight + YC] = wall;
		}
		for ( size_t i = 2; i < XC - 1; i++ ){
			m_map[2][i*s_mapHeight + YC - 2] = wall;
		}
		for ( size_t i = 2; i < XC - 1; i++ ){
			m_map[5][i*s_mapHeight + YC] = wall;
		}
		for ( size_t i = XC + 2; i < s_mapWidth; i++ ){
			m_map[3][i*s_mapHeight - 1 + YC] = wall;
			m_map[4][i*s_mapHeight + 1 + YC] = wall;
		}
		m_map[3][( XC + 2 )*s_mapHeight - 2 + YC] = wall;
		m_map[3][( XC + 3 )*s_mapHeight - 2 + YC] = wall;
		m_map[4][( XC + 2 )*s_mapHeight + 2 + YC] = wall;
		m_map[4][( XC + 3 )*s_mapHeight + 2 + YC] = wall;
		break;
	}
}
