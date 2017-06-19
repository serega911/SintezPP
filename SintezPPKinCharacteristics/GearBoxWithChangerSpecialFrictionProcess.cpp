#include "../Libraries/Singletons.h"
#include "GearBoxWithChangerSpecialFrictionProcess.h"


NS_CORE MultiLinkArray ari::GearBoxWithChangerSpecialFrictionProcess::getChainsForCurrentGear() const
{
	auto chains = getChains();
	auto drivingElements = m_gearChanger.getDrivingElementsForGear();
	const size_t drivElemSize = drivingElements.size();
	const size_t chainsSize = chains.size();

	int frictionNumber = 0;
	for ( size_t i = 0; i < drivElemSize; i++ )
	{
		const NS_CORE Link& elem = drivingElements[i];

		if ( elem.getElem2() != NS_CORE Element::BRAKE )
		{
			frictionNumber++;
			int frictionSubNumber = 0;
			for ( auto& it : chains )
			{
				if ( it.find( elem.getElem1() ) )
				{
					frictionSubNumber++;
					NS_CORE Link link( elem.getElem1(), NS_CORE Element( NS_CORE eMainElement::FRICTION, NS_CORE GearSetNumber( frictionNumber * 10 + frictionSubNumber ) ) );
					it.addLinkToChain( link );
				}
				if ( it.find( elem.getElem2() ) )
				{
					frictionSubNumber++;
					NS_CORE Link link( elem.getElem2(), NS_CORE Element( NS_CORE eMainElement::FRICTION, NS_CORE GearSetNumber( frictionNumber * 10 + frictionSubNumber ) ) );
					it.addLinkToChain( link );
				}
			}
		}
		else
		{
			for ( auto& it : chains )
			{
				if ( it.find( elem.getElem1() ) )
				{
					it.addLinkToChain( elem );
				}
			}
		}
	}

	chains.reserve( chainsSize + frictionNumber );
	for ( int i = 0; i < frictionNumber; i++ )
	{
		NS_CORE MultiLink ch;
		ch.addLinkToChain( NS_CORE Link(
			NS_CORE Element( NS_CORE eMainElement::FRICTION, NS_CORE GearSetNumber( ( i + 1 ) * 10 + 1 ) ),
			NS_CORE Element( NS_CORE eMainElement::FRICTION, NS_CORE GearSetNumber( ( i + 1 ) * 10 + 2 ) ) ) );
		chains.emplace_back( ch );
	}

	return chains;
}

ari::GearBoxWithChangerSpecialFrictionProcess::GearBoxWithChangerSpecialFrictionProcess( const NS_CORE Code& code )
	: GearBoxWithChanger( code )
{

}
