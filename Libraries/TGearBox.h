#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "TCode.h"
#include "TChain.h"
#include "TGearChanger.h"
#include "TGearNumber.h"

NS_CORE_START

//typedef size_t TGearNumber;						// номер передачи

class TGearBox
{
private:

	TCode										m_code;
	TChainArray									m_chains;
	TGearChanger								m_gearChanger;
	
protected:

	TCode&										getRefferenceToCode();

public:

	TGearBox( const TCode& code );

	const TCode&								getCode() const;
	const TChainArray&								getChains() const;
	TChainArray										getChainsForCurrentGear() const;

	bool										createChains();

	bool										turnOnNextGear();
};

NS_CORE_END
