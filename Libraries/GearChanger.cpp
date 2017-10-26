#include "GearChanger.h"
#include "Singletons.h"
#include "Subset.h"


NS_CORE_USING

std::vector<std::vector<GearChanger::DrivingElementPosition>> core::GearChanger::m_driveElemPostions = {};

GearChanger::GearChanger( const Code& code )
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
		for ( size_t i = 0; i < generalData._numberOfBrakes; i++ )
		{
			m_driveElemPostions.push_back( { DrivingElementPosition( DrivingElementPosition::eType::BRAKE, i ) } );
		}
		m_driveElemPostions.push_back( { DrivingElementPosition( DrivingElementPosition::eType::FRICTION, 0 ) } );
	}
	else if ( initialData._w == 3 )
	{
		// friction + brake
		for ( size_t frict = 0; frict < generalData._numberOfFrictions; frict++ )
		{
			for ( size_t brake = 0; brake < generalData._numberOfBrakes; brake++ )
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
			std::vector<DrivingElementPosition> brakesPositions;
			for ( size_t i = 0; i < generalData._numberOfBrakes; i++ )
				brakesPositions.push_back( DrivingElementPosition( DrivingElementPosition::eType::BRAKE, i ) );

			Subset<std::vector<DrivingElementPosition>> subset( brakesPositions, generalData._numberOfActuatedDrivingElements );

			do
			{
				m_driveElemPostions.push_back( subset.get() );
			} while ( subset.next() );
		}
	}
	else
	{
		Log::warning( true, "W = 1 and W > 3 isn\'t implemented", Log::CRITICAL, HERE );
	}
}

TLinkArray GearChanger::getDrivingElementsForGear( const size_t gear ) const
{
	Log::warning( gear == Singletons::getInstance()->getInitialData()._numberOfGears, "Wrong gear", Log::CRITICAL, HERE );

	return m_drivingElementsForAllGears.at( gear );
}
