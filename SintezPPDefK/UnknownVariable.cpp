#include "UnknownVariable.h"
#include "Variable.h"

using namespace pss;

pss::UnknownVariable::UnknownVariable( const VariableValue & value ) :
m_value(value)
{
}

void pss::UnknownVariable::setValue( const VariableValue & value )
{
	m_value = value;
	callAllListeners();
}

void pss::UnknownVariable::addListener( Variable* listener )
{
	m_listeners.insert( listener );
	listener->onChangeUnknownVariableValue( m_value );
}

void pss::UnknownVariable::deleteListener( Variable* listener )
{
	m_listeners.erase( listener );
}

const std::set<Variable*> pss::UnknownVariable::getAllListeners() const
{
	return m_listeners;
}

bool pss::UnknownVariable::findElementInListeners( const TElement & element )
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

void pss::UnknownVariable::callAllListeners() const
{
	for ( auto & listener : m_listeners )
	{
		listener->onChangeUnknownVariableValue( m_value );
	}
}