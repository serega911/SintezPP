#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "TCode.h"
#include "TChain.h"
#include "TGearChanger.h"
#include "TGearNumber.h"

NS_CORE_START

class TGearBox
{
private:

	TCode										m_code;
	TChainArray									m_chains;
	TGearChanger								m_gearChanger;

	void										makeChains( TChainArray &chains ) const;
	
	
protected:

	TCode&										getRefferenceToCode();

public:

	TGearBox( const TCode& code );

	bool										createChains();

	const TCode&								getCode() const;
	const TChainArray&							getChains() const;
	TChainArray									getChainsForCurrentGear() const;

	bool										turnOnNextGear();
};

NS_CORE_END
