#include "TParser.h"
#include "TSettingsItem.h"

NS_CORE_USING

const char TParser::s_delimiter = '=';

TSettingsItem TParser::parse( const std::string & str )
{
	auto pos = str.find( s_delimiter );
	return TSettingsItem( str.substr( 0, pos ), str.substr( pos + 1, str.npos ) );
}

std::string TParser::pack( const TSettingsItem & line )
{
	return line.m_key + "=" + line.m_value;
}
