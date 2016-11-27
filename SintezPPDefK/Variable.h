#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Defines.h"

#include "../Libraries/Element.h"
#include "../Libraries/GearNumber.h"


NS_ARI_START

class Variable
{
private:

	VariableValue								m_value;
	bool										m_isDefined;
	NS_CORE Element								m_element;
	NS_CORE GearNumber							m_gear;

public:

	void										setDefined( bool isDefined );
	void										setValue( const VariableValue & value );
	void										setElement( const NS_CORE Element & element, const NS_CORE GearNumber& gear );

	NS_CORE Element								getElement() const;
	bool										getDefined() const;
	VariableValue								getValue() const;
	NS_CORE GearNumber							getGear() const;

	void										onChangeUnknownVariableValue( const VariableValue & newValue );
};

NS_ARI_END