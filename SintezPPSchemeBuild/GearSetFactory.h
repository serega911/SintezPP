#pragma once

#include <memory>

#include "ISchemeElement.h"
#include "Cordinate.h"
#include "eGearSetType.h"


NS_ARI_START

class GearSetFactory
{
private:

	std::shared_ptr<ISchemeElement>					createStandart( const Cordinate& anchor );
	std::shared_ptr<ISchemeElement>					createCustom( const Cordinate& anchor, const bool flipX, const bool flipY );


public:
	GearSetFactory();
	~GearSetFactory();

	std::shared_ptr<ISchemeElement>					createGearSet( eGearSetType type, const Cordinate& anchor );
};

NS_CORE_END