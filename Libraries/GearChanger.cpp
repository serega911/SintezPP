#include "GearChanger.h"
#include "Singletons.h"
#include "CombinatoricsValueArray.h"


NS_CORE_USING

std::vector<std::vector<GearChanger::DrivingElementPosition>> core::GearChanger::m_driveElemPostions = {};

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
			DrivingElementPosition pos = m_driveElemPostions[i][j];
			m_drivingElementsForAllGears[i][j] = ( pos._type == GearChanger::DrivingElementPosition::BRAKE ) ?
				code.getBrakes()[pos._pos] : code.getFrictions()[pos._pos];
		}
	}
}

void GearChanger::initDriveElemPositions()
{
	const auto& generalData = Singletons::getInstance()->getGeneralData();
	const auto& initialData = Singletons::getInstance()->getInitialData();
	const auto& settings = Singletons::getInstance()->getSettings()->getGeneralSettings();

	m_driveElemPostions.reserve( initialData._numberOfGears );

	if ( initialData._w == 2 )
	{
		for ( size_t i = 0; i < initialData._numberOfGears; i++ )
		{
			m_driveElemPostions.push_back( { DrivingElementPosition( DrivingElementPosition::eType::BRAKE, i ) } );
		}
	}
	else if ( initialData._w == 3 )
	{
		// friction + brake
		for ( int frict = 0; frict < generalData._numberOfFrictions; frict++ )
		{
			for ( int brake = 0; brake < generalData._numberOfBrakes; brake++ )
			{
				m_driveElemPostions.push_back( { 
					DrivingElementPosition( DrivingElementPosition::eType::FRICTION, frict ),
					DrivingElementPosition( DrivingElementPosition::eType::BRAKE, brake ) 
				} );
			}

		}
		// friction + friction
		if ( settings._gearChangerUseTwoFrictions )
			m_driveElemPostions.push_back( {
				DrivingElementPosition( DrivingElementPosition::eType::FRICTION, 0 ),
				DrivingElementPosition( DrivingElementPosition::eType::FRICTION, 1 )
			} );
		// brake + brake
		if ( settings._gearChangerUseTwoBrakes )
		{
			size_t i = 0;
			CombinatoricsValueArray combi;
			while ( NS_CORE Singletons::getInstance()->getCombinatorics()->getSubset( generalData._numberOfBrakes, generalData._numberOfActuatedDrivingElements, i++, combi ) )
			{
				std::vector<DrivingElementPosition> brakesPos;
				const size_t combiSize = combi.size();
				for ( size_t i = 0; i < combiSize; i++ )
					brakesPos.push_back( DrivingElementPosition( DrivingElementPosition::eType::BRAKE, combi[i] ) );
				m_driveElemPostions.push_back( brakesPos );
			}
		}
	}
	else
	{
		Log::warning( true, "W = 1 and W > 3 isn\'t implemented", Log::CRITICAL, HERE );
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
