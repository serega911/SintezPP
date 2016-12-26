#include "../Libraries/GearBox.h"

#include "Scheme.h"

NS_ARI_USING

Scheme::Scheme( const NS_CORE Code& code )
{
	NS_CORE GearBox gb( code );
	gb.createChains();

	m_chains = gb.getChains();
}

