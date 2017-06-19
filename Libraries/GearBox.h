#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "Code.h"
#include "Chain.h"

#include "GearNumber.h"
#include "ChainArray.h"

NS_CORE_START

class GearBox
{
private:

	Code										m_code;
	ChainArray									m_chains;

protected:

	void										makeChains( ChainArray &chains ) const;
	Code&										getRefferenceToCode();

public:

	GearBox( const Code& code );

	void										createChains();

	const Code&									getCode() const;
	const ChainArray&							getChains() const;

};

NS_CORE_END
