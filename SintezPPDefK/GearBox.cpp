#include "GearBox.h"

NS_ARI_USING

GearBox::GearBox( const NS_CORE Code& code )
	: Parent( code ), m_gearChanger( code )
{
}

NS_CORE ChainArray GearBox::getChainsForCurrentGear() const
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

bool GearBox::turnOnNextGear()
{
	return m_gearChanger.next();
}