#pragma once

#include<vector>
#include "GlobalDefines.h"
#include "Log.h"

NS_CORE_START

enum class eMainElement
{
	EMPTY = 0
	, SUN_GEAR = 'S'
	, EPICYCLIC_GEAR = 'E'
	, CARRIER = 'C'
	, INPUT = 'I'
	, OUTPUT = 'O'
	, BRAKE = 'B'
	, SATTELITE = 'X'
};

inline char convernToSymbol( const eMainElement& e )
{
	return static_cast<char>( e );
}

inline eMainElement convernToMainElement( const char symbol )
{
	return static_cast<eMainElement>( symbol );
}

inline int convernToInt( const eMainElement& e )
{
	int ret = 0;

	switch ( e )
	{
	case eMainElement::SUN_GEAR:
		ret = 1;
		break;
	case eMainElement::EPICYCLIC_GEAR:
		ret = 2;
		break;
	case eMainElement::CARRIER:
		ret = 3;
		break;
	default:
		Log::warning( true, "Wrong convertation from eMainElement to int.", Log::CRITICAL, HERE );
		break;
	}

	return ret;
}

inline bool isCentralElement( const eMainElement& e )
{
	return e == eMainElement::SUN_GEAR || e == eMainElement::EPICYCLIC_GEAR || e == eMainElement::CARRIER;
}

inline bool isAdditionalElement( const  eMainElement& e )
{
	return e == eMainElement::INPUT || e == eMainElement::OUTPUT || e == eMainElement::BRAKE;
}

NS_CORE_END
