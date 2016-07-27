#pragma once

#include "TLog.h"

namespace pss
{
	enum class eMainElement
	{
		EMPTY = 0
		, SUN_GEAR
		, EPICYCLIC_GEAR
		, CARRIER
		, INPUT
		, OUTPUT
		, BRAKE
	};

	inline char convernToSymbol( const eMainElement& e )
	{
		char res;

		switch ( e )
		{
		case eMainElement::SUN_GEAR:
			res = 'S';
			break;
		case eMainElement::EPICYCLIC_GEAR:
			res = 'E';
			break;
		case eMainElement::CARRIER:
			res = 'C';
			break;
		case eMainElement::INPUT:
			res = 'I';
			break;
		case eMainElement::OUTPUT:
			res = 'O';
			break;
		case eMainElement::BRAKE:
			res = 'B';
			break;
		default:
			TLog::warning( true, "Wrong eMainElement value", TLog::CRITICAL, "eMainElement.h" );
			break;
		}

		return res;
	}

	inline eMainElement convernToMainElement( const char symbol )
	{
		eMainElement res;

		switch ( symbol )
		{
		case 'S':
			res = eMainElement::SUN_GEAR;
			break;
		case 'E':
			res = eMainElement::EPICYCLIC_GEAR;
			break;
		case 'C':
			res = eMainElement::CARRIER;
			break;
		case 'I':
			res = eMainElement::INPUT;
			break;
		case 'O':
			res = eMainElement::OUTPUT;
			break;
		case 'B':
			res = eMainElement::BRAKE;
			break;
		default:
			TLog::warning( true, "Wrong symbol value", TLog::CRITICAL, "eMainElement.h" );
			break;
		}

		return res;
	}

}