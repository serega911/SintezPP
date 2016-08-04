#include "Variable.h"

NS_ARI_USING


void Variable::setValue( const VariableValue & value )
{
	m_value = value;
}

VariableValue Variable::getValue() const
{
	return m_value;
}

int Variable::getGear() const
{
	return m_gear;
}

bool Variable::getDefined() const
{
	return m_isDefined;
}

void Variable::setDefined( bool isDefined )
{
	m_isDefined = isDefined;
}

void Variable::onChangeUnknownVariableValue( const VariableValue & newValue )
{
	setValue( newValue );
}

void Variable::setElement( const NS_CORE TElement & element, const int gear )
{
	m_element = element;
	m_gear = gear;
}

NS_CORE TElement Variable::getElement() const
{
	return m_element;
}