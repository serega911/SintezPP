#include "UnknownVariable.h"
#include "Variable.h"

NS_PSS_USING

UnknownVariable::UnknownVariable( const VariableValue & value ) :
m_value(value)
{
}

void UnknownVariable::setValue( const VariableValue & value )
{
	m_value = value;
	callAllListeners();
}

void UnknownVariable::addListener( Variable* listener )
{
	m_listeners.insert( listener );
	listener->onChangeUnknownVariableValue( m_value );
}

void UnknownVariable::deleteListener( Variable* listener )
{
	m_listeners.erase( listener );
}

const std::set<Variable*> UnknownVariable::getAllListeners() const
{
	return m_listeners;
}

bool UnknownVariable::findElementInListeners( const TElement & element )
{
	bool result = false;
	for ( const auto & listener : m_listeners )
	{
		auto variable = dynamic_cast<Variable*>( listener );
		if ( variable && variable->getElement() == element )
		{
			result = true;
			break;
		}
	}
	return result;
}

void UnknownVariable::callAllListeners() const
{
	for ( auto & listener : m_listeners )
	{
		listener->onChangeUnknownVariableValue( m_value );
	}
}