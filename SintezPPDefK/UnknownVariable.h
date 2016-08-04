#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Variable.h"
#include "../Libraries/TElement.h"
#include <set>


NS_ARI_START

class UnknownVariable
{
private:

	std::set<Variable*>							m_listeners;

	VariableValue								m_value;

	void										callAllListeners() const;

public:

	explicit UnknownVariable( const VariableValue & value );

	void										setValue( const VariableValue & value );
	VariableValue								getValue() const;

	void										addListener( Variable* listener );
	void										deleteListener( Variable* listener );
	const std::set<Variable*>					getAllListeners() const;

	bool										findElementInListeners( const NS_CORE TElement & element );

};

NS_ARI_END