#include "GearBoxWithChanger.h"

NS_CORE_USING

GearBoxWithChanger::GearBoxWithChanger( const NS_CORE Code& code )
: Parent( code ), m_gearChanger( code )
{
}

NS_CORE ChainArray GearBoxWithChanger::getChainsForCurrentGear() const
{
	auto chains = getChains();
	auto drivingElements = m_gearChanger.getDrivingElementsForGear();
	const size_t drivElemSize = drivingElements.size();
	const size_t chainsSize = chains.size();

	chains.resize( chainsSize + drivElemSize );
	for ( size_t i = 0; i < drivElemSize; i++ )
		chains[chainsSize + i].addLinkToChain( drivingElements[i] );

	makeChains( chains );

	return chains;
}

bool GearBoxWithChanger::turnOnNextGear()
{
	return m_gearChanger.next();
}