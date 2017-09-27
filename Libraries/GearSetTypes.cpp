#include "GearSetTypes.h"
#include "Singletons.h"

NS_CORE_USING


void GearSetTypes::writeToFile( std::ostream& file ) const
{
	for ( auto& it : m_types )
		file << ' ' << convernToString( it.second );
}

bool GearSetTypes::loadFromFile( std::istream& file )
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

void GearSetTypes::add( const GearSetNumber& gearSetN, const eGearSetType& type )
{
	m_types[gearSetN] = type;
}

const eGearSetType&	GearSetTypes::get(const GearSetNumber& set) const
{
	return m_types.at(set);
}