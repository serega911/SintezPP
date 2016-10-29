#include "Equations.h"
#include "VariablesSet.h"

NS_ARI_USING

 FunctionValue Equations::wyllys( const VariablesSet & set )
 {
	 return set[NS_CORE eMainElement::SUN_GEAR].getValue()
		 - set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue() *	set[NS_CORE eMainElement::EMPTY].getValue()
		 + set[NS_CORE eMainElement::CARRIER].getValue() *			( set[NS_CORE eMainElement::EMPTY].getValue() - 1.0f );
 }
 
 FunctionValue Equations::empty( const VariablesSet & set )
 {
	return 0.0f;
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
		NS_CORE Log::warning( true, "wrong eMainElement value", NS_CORE Log::CRITICAL, "Equations::getEquation" );
		break;
	}
 }

 FunctionValue Equations::dfDk( const VariablesSet & set )
 {
	 return -set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue() + set[NS_CORE eMainElement::CARRIER].getValue();
 }

 FunctionValue Equations::dfDw1( const VariablesSet & set )
 {
	 return 1.0f;
 }

 FunctionValue Equations::dfDw2( const VariablesSet & set )
 {
	 return -set[NS_CORE eMainElement::EMPTY].getValue();
 }

 FunctionValue Equations::dfDw3( const VariablesSet & set )
 {
	 return set[NS_CORE eMainElement::EMPTY].getValue() - 1.0f;
 }

 FunctionValue Equations::calcWEpicyclic( const VariablesSet & set )
 {
	 return (
		 set[NS_CORE eMainElement::SUN_GEAR].getValue() +
		 set[NS_CORE eMainElement::CARRIER].getValue() * ( set[NS_CORE eMainElement::EMPTY].getValue() - 1.0f )
		 ) / set[NS_CORE eMainElement::EMPTY].getValue();
 }

 FunctionValue Equations::calcWSun( const VariablesSet & set )
 {
	 return set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue() *	set[NS_CORE eMainElement::EMPTY].getValue()
		 - set[NS_CORE eMainElement::CARRIER].getValue() *		( set[NS_CORE eMainElement::EMPTY].getValue() - 1.0f );
 }

 FunctionValue Equations::calcWCarrirer( const VariablesSet & set )
 {
	 return (
		 -set[NS_CORE eMainElement::SUN_GEAR].getValue()
		 + set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue() *	set[NS_CORE eMainElement::EMPTY].getValue()
		 ) / ( set[NS_CORE eMainElement::EMPTY].getValue() - 1.0f );
 }

 FunctionValue Equations::calcKValue( const VariablesSet & set )
 {
	 return
		 (
		 set[NS_CORE eMainElement::CARRIER].getValue() - set[NS_CORE eMainElement::SUN_GEAR].getValue()
		 ) / (
		 set[NS_CORE eMainElement::CARRIER].getValue() - set[NS_CORE eMainElement::EPICYCLIC_GEAR].getValue()
		 );
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
		 NS_CORE Log::warning( true, "wrong eMainElement value", NS_CORE Log::CRITICAL, "Equations::calcOne" );
		 break;
	 }
 }
