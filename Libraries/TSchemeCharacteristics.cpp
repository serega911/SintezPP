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
}

void core::TSchemeCharacteristics::setKinematicScheneData( size_t radial, size_t axial )
{
	m_kinematicSchemeData._radialRoads = radial;
	m_kinematicSchemeData._axialRoads = axial;
}
