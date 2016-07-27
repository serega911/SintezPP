#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Defines.h"

#include "../Libraries/TElement.h"


NS_PSS_START

class Variable
{
private:

	VariableValue								m_value;
	bool										m_isDefined;
	TElement									m_element;
	int											m_gear;

public:

	void										setDefined( bool isDefined );
	void										setValue( const VariableValue & value );
	void										setElement( const TElement & element, const int gear );

	TElement									getElement() const;
	bool										getDefined() const;
	VariableValue								getValue() const;
	int											getGear() const;

	void										onChangeUnknownVariableValue( const VariableValue & newValue );

};

NS_PSS_END