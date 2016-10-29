#pragma once

#include "PlanetaryGearSet.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/GearBox.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/KinematicSchemeData.h"
#include "Cordinates.h"
#include "Viewer_fwd.h"
#include <vector>

NS_ARI_START

class KinematicScheme
{
private:

	friend class Viewer;

	std::vector<PlanetaryGearSet>				m_field;
	NS_CORE Code								m_code;
	NS_CORE InternalGearRatios									m_k;

public:

	const NS_CORE ChainArray&					operator[]( int xPos ) const;
	NS_CORE ChainArray&						operator[]( int xPos );

	void										addGearSet(const PlanetaryGearSet & gearSet);
	void										addRoute( const TCordinatesArray & cord, const NS_CORE Link & link );
	void										addFakeRoute( const TCordinatesArray & cord, const NS_CORE Link & link );
	void										addBorders();

	void										print();

	void										create( const NS_CORE Code& code, const NS_CORE InternalGearRatios & k );
	size_t										size() const;

	NS_CORE KinematicSchemeData					getKinemaricSchemeCharacteristics() const;

};

NS_ARI_END


