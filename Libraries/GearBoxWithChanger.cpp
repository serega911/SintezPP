#include "GearBoxWithChanger.h"
#include "../Libraries/Singletons.h"

NS_CORE_USING

GearBoxWithChanger::GearBoxWithChanger( const NS_CORE Code& code )
: Parent( code ), m_gearChanger( code ), m_gear( 0 )
{
}

NS_CORE MultiLinkArray GearBoxWithChanger::getChainsForCurrentGear() const
{
	return m_gearsChains.at( m_gear );
}

void core::GearBoxWithChanger::createGear()
{
	if ( m_gearsChains.find( m_gear ) == m_gearsChains.end() )
	{
		if ( !isChainsCreatd() )
			createChains();

		auto chains = getChains();

		auto drivingElements = m_gearChanger.getDrivingElementsForGear( m_gear );
		const size_t drivElemSize = drivingElements.size();
		const size_t chainsSize = chains.size();

		chains.resize( chainsSize + drivElemSize );
		for ( size_t i = 0; i < drivElemSize; i++ )
			chains[chainsSize + i].addLinkToChain( drivingElements[i] );

		makeChains( chains );

		m_gearsChains[m_gear] = chains;
	}
}


bool GearBoxWithChanger::turnOnNextGear()
{
	if ( ( ++m_gear ) == NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears )
		return false;

	createGear();
	return true;
}

void core::GearBoxWithChanger::reset()
{
	m_gear = 0;
	createGear();
}
