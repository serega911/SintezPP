#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Defines.h"

#include "../Libraries/TElement.h"


NS_ARI_START

class Variable
{
private:

	VariableValue								m_value;
	bool										m_isDefined;
	NS_CORE TElement							m_element;
	int											m_gear;

public:

	void										setDefined( bool isDefined );
	void										setValue( const VariableValue & value );
	void										setElement( const NS_CORE TElement & element, const int gear );

	NS_CORE TElement							getElement() const;
	bool										getDefined() const;
	VariableValue								getValue() const;
	int											getGear() const;

	void										onChangeUnknownVariableValue( const VariableValue & newValue );
};

NS_ARI_END