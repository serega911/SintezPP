#include "Equations.h"
#include "VariablesSet.h"

NS_ARI_USING

bool Equations::s_statusOK = true;

FunctionValue Equations::wyllys( const VariablesSet & set )
{
	return set[NS_CORE eMainElement::SUN_GEAR].getValue()
		- set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue() *	set[NS_CORE eMainElement::EMPTY].getValue()
		+ set[NS_CORE eMainElement::CARRIER].getValue() *			( set[NS_CORE eMainElement::EMPTY].getValue() - 1.0f );
}

FunctionValue Equations::empty( const VariablesSet & set )
{
	return 0.0;
}

const Equation Equations::getEquation( const NS_CORE eMainElement & elem )
{
	switch ( elem )
	{
	case NS_CORE eMainElement::SUN_GEAR:
		return dfDw1;
		break;
	case NS_CORE eMainElement::EPICYCLIC_GEAR:
		return dfDw2;
		break;
	case NS_CORE eMainElement::CARRIER:
		return dfDw3;
		break;
	case NS_CORE eMainElement::EMPTY:
		return dfDk;
		break;
	default:
		NS_CORE Log::warning( true, "wrong eMainElement value", NS_CORE Log::CRITICAL, HERE );
		return nullptr;
		break;
	}
}

void Equations::resetStatusOK()
{
	s_statusOK = true;
}

bool Equations::getStatusOK()
{
	return s_statusOK;
}

void Equations::setStatusFail()
{
	s_statusOK = false;
}

void ari::Equations::processBadCondition( const bool condition, const std::string & message /*= "" */ )
{
	if ( condition )
	{
		//NS_CORE Log::warning( condition, message, NS_CORE Log::NON_CRITICAL, HERE );
		setStatusFail();
	}
}

FunctionValue Equations::dfDk( const VariablesSet & set )
{
	return -set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue() + set[NS_CORE eMainElement::CARRIER].getValue();
}

FunctionValue Equations::dfDw1( const VariablesSet & set )
{
	return 1.0;
}

FunctionValue Equations::dfDw2( const VariablesSet & set )
{
	return -set[NS_CORE eMainElement::EMPTY].getValue();
}

FunctionValue Equations::dfDw3( const VariablesSet & set )
{
	return set[NS_CORE eMainElement::EMPTY].getValue() - 1.0;
}

FunctionValue Equations::calcWEpicyclic( const VariablesSet & set )
{
	const auto z = set[NS_CORE eMainElement::EMPTY].getValue();

	processBadCondition( z == 0, "division by ZERO" );

	return (
		set[NS_CORE eMainElement::SUN_GEAR].getValue() +
		set[NS_CORE eMainElement::CARRIER].getValue() * ( set[NS_CORE eMainElement::EMPTY].getValue() - 1.0f )
		) / z;
}

FunctionValue Equations::calcWSun( const VariablesSet & set )
{
	return set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue() *	set[NS_CORE eMainElement::EMPTY].getValue()
		- set[NS_CORE eMainElement::CARRIER].getValue() *		( set[NS_CORE eMainElement::EMPTY].getValue() - 1.0f );
}

FunctionValue Equations::calcWCarrirer( const VariablesSet & set )
{
	const auto z = set[NS_CORE eMainElement::EMPTY].getValue() - 1.0;

	processBadCondition( z == 0, "division by ZERO" );

	return (
		-set[NS_CORE eMainElement::SUN_GEAR].getValue()
		+ set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue() *	set[NS_CORE eMainElement::EMPTY].getValue()
		) / z;
}

FunctionValue Equations::calcKValue( const VariablesSet & set )
{
	const auto z = set[NS_CORE eMainElement::CARRIER].getValue() - set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue();

	processBadCondition( z == 0, "division by ZERO" );

	return ( set[NS_CORE eMainElement::CARRIER].getValue() - set[NS_CORE eMainElement::SUN_GEAR].getValue() ) / z;
}

bool ari::Equations::check( const VariablesSet & set )
{
	return abs( set[NS_CORE eMainElement::EMPTY].getValue() ) > 0.0001 && abs( wyllys( set ) ) < 0.0001;
}

ari::FunctionValue ari::Equations::calcOne( const NS_CORE eMainElement elem, const VariablesSet & set )
{
	switch ( elem )
	{
	case NS_CORE eMainElement::SUN_GEAR:
		return calcWSun( set );
		break;
	case NS_CORE eMainElement::EPICYCLIC_GEAR:
		return calcWEpicyclic( set );
		break;
	case NS_CORE eMainElement::CARRIER:
		return calcWCarrirer( set );
		break;
	case NS_CORE eMainElement::EMPTY:
		return calcKValue( set );
		break;
	default:
		NS_CORE Log::warning( true, "wrong eMainElement value", NS_CORE Log::CRITICAL, HERE );
		return FunctionValue( 0 );
		break;
	}
}
