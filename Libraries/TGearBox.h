#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "GlobalTypes.h"
#include "TCode.h"
#include "TChain.h"
#include "TGearChanger.h"

NS_CORE_START

typedef std::vector<TChain> TChains;
typedef std::vector<TElement> TElements;

class TGearBox
{
private:

	TCode										m_code;
	TChains										m_chains;
	TGearChanger								m_gearChanger;
	
protected:

	TCode&										getRefferenceToCode();

public:

	TGearBox( const TCode& code );

	const TCode&								getCode() const;
	const TChains&								getChains() const;
	TChains										getChainsForCurrentGear() const;

	bool										createChains();

	bool										turnOnNextGear();
};

NS_CORE_END
