#include "GearChanger.h"
#include "Singletons.h"
#include "CombinatoricsValueArray.h"


NS_CORE_USING

std::vector<std::vector<size_t>> core::GearChanger::m_driveElemPostions = {};

GearChanger::GearChanger( const Code& code )
: m_gear( 0 )
{
	if ( m_driveElemPostions.size() == 0 )
	{
		initDriveElemPositions();
	}

	const size_t drElemPosSize = m_driveElemPostions.size();

	m_drivingElementsForAllGears.resize( drElemPosSize );
	for ( size_t i = 0; i < drElemPosSize; i++ )
	{
		m_drivingElementsForAllGears[i].resize( m_driveElemPostions[i].size() );
		for ( size_t j = 0; j < m_driveElemPostions[i].size(); j++ )
		{
			m_drivingElementsForAllGears[i][j] = code.getCode()[m_driveElemPostions[i][j]];
		}
	}
}

void GearChanger::initDriveElemPositions()
{
	const auto& generalData = Singletons::getInstance()->getGeneralData();
	const auto& initialData = Singletons::getInstance()->getInitialData();
	const auto& settings = Singletons::getInstance()->getSettings()->getGeneralSettings();

	size_t startPosFrictions = 2 + generalData._numberOfLinks;
	size_t startPosBrakes = startPosFrictions + generalData._numberOfFrictions;

	m_driveElemPostions.reserve( initialData._numberOfGears );

	if ( initialData._w == 2 )
	{
		for ( size_t i = 0; i < initialData._numberOfGears; i++ )
		{
			m_driveElemPostions.push_back( { startPosBrakes + i } );
		}
	}
	else if ( initialData._w == 3 )
	{
		// friction + brake
		for ( int frict = 0; frict < generalData._numberOfFrictions; frict++ )
		{
			for ( int brake = 0; brake < generalData._numberOfBrakes; brake++ )
			{
				m_driveElemPostions.push_back( { startPosFrictions + frict, startPosBrakes + brake } );
			}

		}
		// friction + friction
		if ( settings._gearChangerUseTwoFrictions )
			m_driveElemPostions.push_back( { startPosFrictions, startPosFrictions + 1 } );
		// brake + brake
		if ( settings._gearChangerUseTwoBrakes )
		{
			size_t i = 0;
			CombinatoricsValueArray combi;
			while ( NS_CORE Singletons::getInstance()->getCombinatorics()->getSubset( generalData._numberOfBrakes, generalData._numberOfActuatedDrivingElements, i++, combi ) )
			{
				std::vector<size_t> brakesPos;
				const size_t combiSize = combi.size();
				for ( size_t i = 0; i < combiSize; i++ )
					brakesPos.push_back( startPosBrakes + combi[i] );
				m_driveElemPostions.push_back( brakesPos );
			}
		}
	}
	else
	{
		Log::warning( true, "W = 1 and W > 3 isn\'t implemented", Log::CRITICAL, "TGearChanger::TGearChanger( const TCode& code )" );
	}
}

TLinkArray GearChanger::getDrivingElementsForGear() const
{
	return m_drivingElementsForAllGears.at(m_gear);
}

bool GearChanger::next()
{
	m_gear++;

	return m_gear < Singletons::getInstance()->getInitialData()._numberOfGears;
}
