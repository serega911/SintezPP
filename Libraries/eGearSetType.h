#pragma once;

#include <string>
#include "GlobalDefines.h"
#include "Log.h"

NS_CORE_START

enum class eGearSetType
{
	TYPE_N,
	TYPE_N_REVERSE,
	TYPE_U,
	TYPE_U_REVERSE,
	TYPE_DEFAULT
};

inline std::string convernToString( const eGearSetType& e )
{
	switch ( e )
	{
	case eGearSetType::TYPE_N:			return "N";		break;
	case eGearSetType::TYPE_N_REVERSE:	return "N_R";	break;
	case eGearSetType::TYPE_U:			return "U";		break;
	case eGearSetType::TYPE_U_REVERSE:	return "U_R";	break;
	case eGearSetType::TYPE_DEFAULT:	return "D";		break;
	default:
		Log::warning( true, "wrong type", Log::eWarningImportance::CRITICAL, HERE );
		return "";
		break;
	}
}

inline eGearSetType convernToGearSetType( const std::string& str )
{
	if ( str == "W" )
		return eGearSetType::TYPE_N;
	else if (str == "N_R")
		return eGearSetType::TYPE_N_REVERSE;
	else if (str == "U")
		return eGearSetType::TYPE_U;
	else if ( str == "U_R" )
		return eGearSetType::TYPE_U_REVERSE;
	else if (str == "D")
		return eGearSetType::TYPE_DEFAULT;
	else
		Log::warning( true, "wrong type:" + str, Log::eWarningImportance::CRITICAL, HERE );
}

NS_CORE_END