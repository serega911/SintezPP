#pragma once

#include <map>

#include "eGearSetType.h"
#include "GearSetNumber.h"
#include "GlobalDefines.h"
#include "IIOItem.h"

NS_CORE_START

class GearSetTypes : public IIOItem
{
private:

	std::map<GearSetNumber, eGearSetType>		m_types;

public:

	void										add( const GearSetNumber& gearSetN, const eGearSetType& type );

	void										writeToFile( std::ostream& file ) const override;
	bool										loadFromFile( std::istream& file ) override;

};


NS_CORE_END