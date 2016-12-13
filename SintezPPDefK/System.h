#pragma once

#include "../Libraries/GlobalDefines.h"

#include <vector>
#include <map>
#include <set>

#include "UnknownVariable.h"
#include "VariablesSet.h"
#include "../Libraries/Chain.h"
#include "../Libraries/GearBox.h"
#include "../Libraries/GearNumber.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/Ratios.h"

NS_ARI_START

class System
{
private:

	std::vector<std::vector<VariablesSet>>		m_sets;
	UnknownVariableArray						m_unknowns;
	size_t										m_addedSetCount;

	void										addDefinedChain( const NS_CORE Chain& chain, const VariableValue & value, const NS_CORE GearNumber& gear );
	void										addUndefinedChain( const NS_CORE Chain& chain, const VariableValue & value, const NS_CORE GearNumber& gear );

public:

	System();

	void										init( const NS_CORE InternalGearRatios& initialKValues );
	bool										addGearChains( const NS_CORE ChainArray& chains, const NS_CORE GearNumber& gear, const NS_CORE RatioValue i );

	VariablesSet &								getVariablesSet( const NS_CORE GearNumber& gearN, const int & gearSetN );
	const VariablesSet &						getVariablesSet( const NS_CORE GearNumber& gearN, const int & gearSetN ) const;
	UnknownVariableArray &						getUnknownVariables();
	const UnknownVariableArray &				getUnknownVariables() const;
};

NS_ARI_END