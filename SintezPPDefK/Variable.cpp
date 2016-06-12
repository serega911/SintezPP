#include "Variable.h"

NS_PSS_USING


void Variable::setValue( const VariableValue & value )
{
	m_value = value;
}

VariableValue Variable::getValue() const
{
	return m_value;
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

void Variable::setElement( const TElement & element )
{
	m_element = element;
}

TElement Variable::getElement() const
{
	return m_element;
}