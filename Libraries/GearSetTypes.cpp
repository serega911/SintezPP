#include "GearSetTypes.h"
#include "Singletons.h"

NS_CORE_USING


void core::GearSetTypes::writeToFile( std::ostream& file ) const
{
	for ( auto& it : m_types )
		file << ' ' << convernToString( it.second );
}

bool core::GearSetTypes::loadFromFile( std::istream& file )
{
	const int count = Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	for ( int i = 0; i < count; i++ )
	{
		std::string str;
		file >> str;
		m_types[GearSetNumber( i + 1 )] = convernToGearSetType( str );
	}

	return !file.eof();
}

void core::GearSetTypes::add( const GearSetNumber& gearSetN, const eGearSetType& type )
{
	m_types[gearSetN] = type;
}

