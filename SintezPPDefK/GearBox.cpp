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

	chains.resize( chains.size() + drivingElements.size() );

	for ( size_t i = 0; i < drivingElements.size(); i++ )
		chains[chains.size() - i - 1].addLinkToChain( drivingElements[i] );

	makeChains( chains );

	return chains;
}

bool GearBox::turnOnNextGear()
{
	return m_gearChanger.next();
}