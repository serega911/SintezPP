#include "Equations.h"
#include "VariablesSet.h"

NS_PSS_USING

 FunctionValue Equations::wyllys( const VariablesSet & set )
 {
	 return set[eMainElement::SUN_GEAR].getValue()
		 - set[eMainElement::EMPTY].getValue()*set[eMainElement::EPICYCLIC_GEAR].getValue()
		 + ( set[eMainElement::EMPTY].getValue() - 1.0f ) * set[eMainElement::CARRIER].getValue();
 }
 
 FunctionValue Equations::empty( const VariablesSet & set )
 {
	return 0.0f;
 }

 const Equation Equations::getEquation( const eMainElement & elem )
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

 FunctionValue Equations::dfDk( const VariablesSet & set )
 {
	 return - set[eMainElement::EPICYCLIC_GEAR].getValue() + set[eMainElement::CARRIER].getValue();
 }

 FunctionValue Equations::dfDw1( const VariablesSet & set )
 {
	 return 1.0f;
 }

 FunctionValue Equations::dfDw2( const VariablesSet & set )
 {
	 return - set[eMainElement::EMPTY].getValue();
 }

 FunctionValue Equations::dfDw3( const VariablesSet & set )
 {
	 return set[eMainElement::EMPTY].getValue() - 1.0f;
 }
