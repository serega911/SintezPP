#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "Code.h"
#include "Chain.h"
#include "GearChanger.h"
#include "GearNumber.h"
#include "ChainArray.h"

NS_CORE_START

class GearBox
{
private:

	Code										m_code;
	ChainArray									m_chains;
	GearChanger								m_gearChanger;

	void										makeChains( ChainArray &chains ) const;
	
	
protected:

	Code&										getRefferenceToCode();

public:

	GearBox( const Code& code );

	bool										createChains();

	const Code&								getCode() const;
	const ChainArray&							getChains() const;
	ChainArray									getChainsForCurrentGear() const;

	bool										turnOnNextGear();
};

NS_CORE_END
