#include "Variable.h"

using namespace pss;


void pss::Variable::setValue( const VariableValue & value )
{
	m_value = value;
}

VariableValue pss::Variable::getValue() const
{
	return m_value;
}

bool pss::Variable::getDefined() const
{
	return m_isDefined;
}

void pss::Variable::setDefined( bool isDefined )
{
	m_isDefined = isDefined;
}

void pss::Variable::onChangeUnknownVariableValue( const VariableValue & newValue )
{
	setValue( newValue );
}

void pss::Variable::setElement( const TElement & element )
{
	m_element = element;
}

pss::TElement pss::Variable::getElement() const
{
	return m_element;
}