#pragma once

#include "../Libraries/GlobalDefines.h"

#include <vector>
#include <map>
#include <set>

#include "UnknownVariable.h"
#include "VariablesSet.h"
#include "../Libraries/TChain.h"
#include "../Libraries/TK.h"

NS_PSS_START

class System
{
private:

	std::vector<std::vector<VariablesSet>>		m_sets;
	std::vector<UnknownVariable>				m_unknowns;
	size_t										m_addedSetCount;

	void										addDefinedChain( const TChain& chain, const VariableValue & value );
	void										addUndefinedChain( const TChain& chain, const VariableValue & value );

	

public:

	System();

	void										init( const TK& initialKValues );
	void										addGearChains( const std::vector<TChain>& chains, const TElement& brake, double i );

	VariablesSet &								getVariablesSet( const int & gearN, const int & gearSetN );
	const VariablesSet &						getVariablesSet( const int & gearN, const int & gearSetN ) const;
	std::vector<UnknownVariable> &				getUnknownVariables();
	const std::vector<UnknownVariable> &		getUnknownVariables() const;
};

NS_PSS_END