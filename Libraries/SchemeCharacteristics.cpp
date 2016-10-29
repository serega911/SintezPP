#include "SchemeCharacteristics.h"

NS_CORE_USING

size_t core::SchemeCharacteristics::size() const
{
	return 2;
}

void core::SchemeCharacteristics::writeToFile( std::ostream& file ) const
{
	file << m_kinematicSchemeData._axialRoads << ' ' << m_kinematicSchemeData._radialRoads;
}

bool core::SchemeCharacteristics::loadFromFile( std::istream& file )
{
	file >> m_kinematicSchemeData._axialRoads >> m_kinematicSchemeData._radialRoads;

	return true;
}

void core::SchemeCharacteristics::setKinematicScheneData( const KinematicSchemeData& data )
{
	m_kinematicSchemeData = data;
}
