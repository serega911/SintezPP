#pragma once

#include "TPlanetaryGearSet.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/TGearBox.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/KinematicSchemeData.h"
#include "TCordinates.h"
#include "TViewer_fwd.h"
#include <vector>

NS_ARI_START

class TKinematicScheme
{
private:

	friend class TViewer;

	std::vector<TPlanetaryGearSet>				m_field;
	NS_CORE TCode								m_code;
	NS_CORE TK									m_k;

public:

	const NS_CORE TChainArray&					operator[]( int xPos ) const;
	NS_CORE TChainArray&						operator[]( int xPos );

	void										addGearSet(const TPlanetaryGearSet & gearSet);
	void										addRoute( const TCordinatesArray & cord, const NS_CORE TLink & link );
	void										addFakeRoute( const TCordinatesArray & cord, const NS_CORE TLink & link );
	void										addBorders();

	void										print();

	void										create( const NS_CORE TCode& code, const NS_CORE TK & k );
	size_t										size() const;

	NS_CORE KinematicSchemeData					getKinemaricSchemeCharacteristics() const;

};

NS_ARI_END


