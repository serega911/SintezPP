#pragma once

#include "../Libraries/GlobalDefines.h"

#include <vector>
#include <map>
#include <set>

#include "UnknownVariable.h"
#include "VariablesSet.h"
#include "../Libraries/TChain.h"
#include "../Libraries/TGearBox.h"
#include "../Libraries/TGearNumber.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"

NS_ARI_START

class System
{
private:

	std::vector<std::vector<VariablesSet>>		m_sets;
	UnknownVariableArray						m_unknowns;
	size_t										m_addedSetCount;

	void										addDefinedChain( const NS_CORE TChain& chain, const VariableValue & value, const NS_CORE TGearNumber& gear );
	void										addUndefinedChain( const NS_CORE TChain& chain, const VariableValue & value, const NS_CORE TGearNumber& gear );



public:

	System();

	void										init( const NS_CORE TK& initialKValues );
	void										addGearChains( const NS_CORE TChainArray& chains, const NS_CORE TGearNumber& gear, const NS_CORE TIValue i );

	VariablesSet &								getVariablesSet( const NS_CORE TGearNumber& gearN, const int & gearSetN );
	const VariablesSet &						getVariablesSet( const NS_CORE TGearNumber& gearN, const int & gearSetN ) const;
	UnknownVariableArray &						getUnknownVariables();
	const UnknownVariableArray &				getUnknownVariables() const;
};

NS_ARI_END