#include "TSchemeCharacteristics.h"

NS_CORE_USING

size_t core::TSchemeCharacteristics::size() const
{
	return 2;
}

void core::TSchemeCharacteristics::writeToFile( std::ostream& file ) const
{
	file << m_kinematicSchemeData._axialRoads << ' ' << m_kinematicSchemeData._radialRoads;
}

bool core::TSchemeCharacteristics::loadFromFile( std::istream& file )
{
	file >> m_kinematicSchemeData._axialRoads >> m_kinematicSchemeData._radialRoads;

	return true;
}

void core::TSchemeCharacteristics::setKinematicScheneData( const KinematicSchemeData& data )
{
	m_kinematicSchemeData = data;
}
