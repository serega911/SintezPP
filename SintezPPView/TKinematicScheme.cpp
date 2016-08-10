#include "TKinematicScheme.h"
#include "../Libraries/TSingletons.h"

NS_ARI_USING

void TKinematicScheme::init()
{
	m_map.resize( 10 );

	for ( auto& col : m_map )
	{
		col.resize( 10 );
		for ( auto& cell : col )
			cell = NS_CORE TChain();
	}

}
