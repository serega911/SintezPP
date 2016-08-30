#pragma once

#include<vector>
#include "GlobalDefines.h"
#include "TLog.h"

NS_CORE_START

enum class eMainElement;
typedef std::vector<eMainElement> eMainElementArray;

enum class eMainElement
{
	EMPTY = 0
	, SUN_GEAR = 'S'
	, EPICYCLIC_GEAR = 'E'
	, CARRIER = 'C'
	, INPUT = 'I'
	, OUTPUT = 'O'
	, BRAKE = 'B'
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
		TLog::warning( true, "Wrong convertation from eMainElement to int.", TLog::CRITICAL, "inline int convernToInt( const eMainElement& e )" );
		break;
	}

	return ret;
}

NS_CORE_END
