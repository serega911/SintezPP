#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Variable.h"
#include "../Libraries/TElement.h"
#include <set>


NS_PSS_START

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

	bool										findElementInListeners( const TElement & element );

};

NS_PSS_END