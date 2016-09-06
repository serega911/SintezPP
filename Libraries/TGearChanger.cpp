#include "TGearChanger.h"
#include "TSingletons.h"
#include "TCombinatoricsValueArray.h"

NS_CORE_USING


TGearChanger::TGearChanger( const TCode& code )
	: m_gear( 0 )
{
	const auto& generalData = TSingletons::getInstance()->getGeneralData();
	const auto& initialData = TSingletons::getInstance()->getInitialData();
 
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
			driveElemPostions = { { startPosFrictions,		startPosBrakes }
								, { startPosFrictions + 1,	startPosBrakes } };
		}
		else if( 3 == initialData._numberOfPlanetaryGears )
		{
			driveElemPostions = { { startPosFrictions,		startPosBrakes			}
								, { startPosFrictions,		startPosBrakes + 1		}
								, { startPosFrictions+1,	startPosBrakes			}
								, { startPosFrictions+1,	startPosBrakes + 1		}
								, { startPosFrictions,		startPosFrictions + 1	} };
		}
		else
		{
			TLog::warning( true, "W = 1 and W > 3 isn\'t implemented", TLog::CRITICAL, "TGearChanger::TGearChanger( const TCode& code )" );
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

TLinkArray TGearChanger::getDrivingElementsForGear() const
{
	return m_drivingElementsForAllGears[m_gear];
}

bool TGearChanger::next()
{
	m_gear++;

	return m_gear < TSingletons::getInstance()->getInitialData()._numberOfGears;
}
