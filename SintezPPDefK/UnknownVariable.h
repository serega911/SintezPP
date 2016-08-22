#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Variable.h"
#include "../Libraries/TElement.h"
#include "../Libraries/TGearBox.h"
#include <set>


NS_ARI_START

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

	bool										findElementInListeners( const NS_CORE TElement & element, const NS_CORE TGearNumber gear );

	bool										getIsDefined() const;
	void										setLastValue( const VariableValue & value );

};

NS_ARI_END