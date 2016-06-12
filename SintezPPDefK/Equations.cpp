#include "Equations.h"
#include "VariablesSet.h"

using namespace pss;

 pss::FunctionValue pss::Equations::wyllys( const VariablesSet & set )
 {
	return set[eMainElement::EMPTY].getValue( ) - ( set[eMainElement::CARRIER].getValue( ) - set[eMainElement::SUN_GEAR].getValue( ) ) / ( set[eMainElement::CARRIER].getValue( ) - set[eMainElement::EPICYCLIC_GEAR].getValue( ) );
 }
 
 pss::FunctionValue pss::Equations::empty( const VariablesSet & set )
 {
	return 0.0f;
 }

 const Equation pss::Equations::getEquation( const eMainElement & elem )
 {
	switch ( elem )
	{
	case eMainElement::SUN_GEAR :
		return dfDw1;
		break;
	case eMainElement::EPICYCLIC_GEAR:
		return dfDw2;
		break;
	case eMainElement::CARRIER:
		return dfDw3;
		break;
	case eMainElement::EMPTY:
		return dfDk;
		break;
	default:
		//exception
		break;
	}
 }

 pss::FunctionValue pss::Equations::dfDk( const VariablesSet & set )
 {
	 return 1.0f;
 }

 pss::FunctionValue pss::Equations::dfDw1( const VariablesSet & set )
 {
	 return 1.0f / ( set[eMainElement::EPICYCLIC_GEAR].getValue() - set[eMainElement::CARRIER].getValue() );
 }

 pss::FunctionValue pss::Equations::dfDw2( const VariablesSet & set )
 {
	 return ( set[eMainElement::SUN_GEAR].getValue() - set[eMainElement::CARRIER].getValue() ) / pow( ( set[eMainElement::CARRIER].getValue() - set[eMainElement::EPICYCLIC_GEAR].getValue() ), 2 );
 }

 pss::FunctionValue pss::Equations::dfDw3( const VariablesSet & set )
 {
	 return ( set[eMainElement::SUN_GEAR].getValue() - set[eMainElement::EPICYCLIC_GEAR].getValue() ) / pow( ( set[eMainElement::CARRIER].getValue() - set[eMainElement::EPICYCLIC_GEAR].getValue() ), 2 );
 }
