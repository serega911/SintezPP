#include "GearChanger.h"
#include "Singletons.h"
#include "CombinatoricsValueArray.h"

NS_CORE_USING


GearChanger::GearChanger( const Code& code )
	: m_gear( 0 )
{
	const auto& generalData = Singletons::getInstance()->getGeneralData();
	const auto& initialData = Singletons::getInstance()->getInitialData();
 
 	size_t startPosFrictions = 2 + generalData._numberOfLinks;
	size_t startPosBrakes = startPosFrictions + generalData._numberOfFrictions;

	std::vector<std::vector<size_t>> driveElemPostions;

	if ( initialData._w == 2 )
	{
		driveElemPostions.resize( initialData._numberOfGears );
		for ( size_t i = 0; i < initialData._numberOfGears; i++ )
		{
			driveElemPostions[i].push_back( startPosBrakes + i );
		}
	}
	else if ( initialData._w == 3 )
	{
		if ( 2 == initialData._numberOfPlanetaryGears )
		{		
			driveElemPostions = { { startPosFrictions, startPosBrakes }
								, { startPosFrictions, startPosBrakes + 1 }
								, { startPosFrictions + 1, startPosBrakes }
								, { startPosFrictions + 1, startPosBrakes + 1 } };
		}
		else if( 3 == initialData._numberOfPlanetaryGears )
		{
			driveElemPostions = { { startPosFrictions,		startPosBrakes		}
								, { startPosFrictions,		startPosBrakes + 1	}
								, { startPosFrictions,		startPosBrakes + 2	}
								, { startPosFrictions+1,	startPosBrakes		}
								, { startPosFrictions+1,	startPosBrakes + 1	}
								, { startPosFrictions+1,	startPosBrakes + 2	} };
		}
		else
		{
			Log::warning( true, "W = 1 and W > 3 isn\'t implemented", Log::CRITICAL, "TGearChanger::TGearChanger( const TCode& code )" );
		}
	}

	if ( code.size() > startPosFrictions )
	{
		m_drivingElementsForAllGears.resize( driveElemPostions.size() );
		for ( size_t i = 0; i < driveElemPostions.size(); i++ )
		{
			m_drivingElementsForAllGears[i].resize( driveElemPostions[i].size() );
			for ( size_t j = 0; j < driveElemPostions[i].size(); j++ )
			{
				m_drivingElementsForAllGears[i][j] = code.getCode()[driveElemPostions[i][j]];
			}
		}
	}

}

TLinkArray GearChanger::getDrivingElementsForGear() const
{
	return m_drivingElementsForAllGears[m_gear];
}

bool GearChanger::next()
{
	m_gear++;

	return m_gear < Singletons::getInstance()->getInitialData()._numberOfGears;
}
