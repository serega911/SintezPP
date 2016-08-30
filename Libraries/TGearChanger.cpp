#include "TGearChanger.h"
#include "TSingletons.h"

NS_CORE_USING

// TLinkArray TGearChanger::createVector( const TCombinations & replacer ) const
// {
// 	TLinkArray ret;
// 
// 	for ( size_t i = 0; i < replacer.size(); i++ )
// 		ret.push_back( m_drivingElements[replacer[i]] );
// 
// 	return ret;
// }

TGearChanger::TGearChanger( const TCode& code )
	: m_gear( 0 )
{
	const auto& generalData = TSingletons::getInstance()->getGeneralData();
 
 	size_t startPos = 2 + generalData._numberOfLinks;
// 
// 	if ( startPos < code.getCode().size() )
// 	{
// 		m_drivingElements.insert( m_drivingElements.begin(), code.getCode().begin() + startPos, code.getCode().end() );
// 		m_replacer.init( generalData._numberOfActuatedDrivingElements );
// 	}
// 
	//-------------------------------------------------------------------------------------------------------------
	if ( code.size() > startPos )
	{
		TLinkArray frictions( code.getCode().begin() + startPos, code.getCode().end() - generalData._numberOfBrakes );
		TLinkArray brakes( code.getCode().begin() + startPos + generalData._numberOfFrictions, code.getCode().end() );

		const int numberOfActuatedFrictions = TSingletons::getInstance()->getInitialData()._w == 2 ? 0 : 1;
		const int numberOfActuatedBrakes = generalData._numberOfActuatedDrivingElements - numberOfActuatedFrictions;

		if ( frictions.size() == 0 )
		{
			TCombinations replacerBrakes;
			replacerBrakes.init( numberOfActuatedBrakes );
			do
			{
				TLinkArray ret;
				for ( size_t i = 0; i < replacerBrakes.size(); i++ )
					ret.push_back( brakes[replacerBrakes[i]] );
				m_drivingElementsForAllGears.push_back( ret );
			} while ( replacerBrakes.nextReplace( brakes.size() - 1 ) );
		}
		else
		{
			TCombinations replacerFrictions;
			replacerFrictions.init( numberOfActuatedBrakes );
			do
			{
				TLinkArray ret;
				for ( size_t i = 0; i < replacerFrictions.size(); i++ )
					ret.push_back( frictions[replacerFrictions[i]] );

				TCombinations replacerBrakes;
				replacerBrakes.init( numberOfActuatedBrakes );
				do
				{
					TLinkArray tmp = ret;
					for ( size_t i = 0; i < replacerBrakes.size(); i++ )
						tmp.push_back( brakes[replacerBrakes[i]] );
					m_drivingElementsForAllGears.push_back( tmp );
				} while ( replacerBrakes.nextReplace( brakes.size() - 1 ) );

			} while ( replacerFrictions.nextReplace( frictions.size() - 1 ) );
			//fake
			if ( frictions.size() == 2 )
			{
				TLinkArray tmp;
				for ( size_t i = 0; i < frictions.size(); i++ )
					tmp.push_back( frictions[i] );
				m_drivingElementsForAllGears.push_back( tmp );
			}
		}
	}
}

TLinkArray TGearChanger::getDrivingElementsForGear() const
{
	//return createVector( m_replacer );
	return m_drivingElementsForAllGears[m_gear];
}

bool TGearChanger::next()
{
	//const auto& generalData = TSingletons::getInstance()->getGeneralData();

	//return m_replacer.nextReplace( generalData._numberOfFrictions + generalData._numberOfBrakes - 1 );

	m_gear++;

	return m_gear < TSingletons::getInstance()->getInitialData()._numberOfGears;
}
