#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/GlobalTypes.h"

#include <vector>
#include <map>
#include <set>

#include "UnknownVariable.h"
#include "VariablesSet.h"
#include "../Libraries/TChain.h"
#include "../Libraries/TGearBox.h"
#include "../Libraries/TK.h"

NS_ARI_START

class System
{
private:

	std::vector<std::vector<VariablesSet>>		m_sets;
	std::vector<UnknownVariable>				m_unknowns;
	size_t										m_addedSetCount;

	void										addDefinedChain( const NS_CORE TChain& chain, const VariableValue & value, const int gear );
	void										addUndefinedChain( const NS_CORE TChain& chain, const VariableValue & value, const int gear );

	

public:

	System();

	void										init( const NS_CORE TK& initialKValues );
	void										addGearChains( const NS_CORE TChains& chains, const int gear, const double i );

	VariablesSet &								getVariablesSet( const int & gearN, const int & gearSetN );
	const VariablesSet &						getVariablesSet( const int & gearN, const int & gearSetN ) const;
	std::vector<UnknownVariable> &				getUnknownVariables();
	const std::vector<UnknownVariable> &		getUnknownVariables() const;
};

NS_ARI_END