#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Variable.h"
#include "../Libraries/Element.h"
#include "../Libraries/GearBox.h"
#include <set>


NS_ARI_START

class UnknownVariable;
typedef std::vector<UnknownVariable> UnknownVariableArray;

class UnknownVariable
{
private:

	std::set<Variable*>							m_listeners;

	VariableValue								m_value;
	bool										m_isDefined;

	void										callAllListeners() const;

public:

	explicit UnknownVariable( const VariableValue & value );

	void										setValue( const VariableValue & value );
	VariableValue								getValue() const;

	void										addListener( Variable* listener );
	void										deleteListener( Variable* listener );
	const std::set<Variable*>					getAllListeners() const;

	bool										findElementInListeners( const NS_CORE Element & element, const NS_CORE GearNumber gear );

	bool										getIsDefined() const;
	void										setLastValue( const VariableValue & value );

};

NS_ARI_END