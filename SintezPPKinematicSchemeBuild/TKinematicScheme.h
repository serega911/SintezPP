#pragma once

#include "TPlanetaryGearSet.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/GlobalDefines.h"
#include "TCordinates.h"
#include <vector>

NS_ARI_START

class TKinematicScheme
{
private:

	std::vector<TPlanetaryGearSet>				m_field;
	core::TCode									m_code;
	core::TK									m_k;

public:

	const std::vector<core::TChain>&			operator[]( int xPos ) const;
	std::vector<core::TChain>&					operator[]( int xPos );

	void										addGearSet(const TPlanetaryGearSet & gearSet);
	void										addRoute( const std::vector<TCordinates> & cord, const core::TLink & link );
	void										addBorders();

	void										print();

	void										create( const core::TCode& code, core::TK & k );
	size_t										size() const;

};

NS_ARI_END


