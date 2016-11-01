#include "Parser.h"
#include "SettingsItem.h"

NS_CORE_USING

const char Parser::s_delimiter = '=';

SettingsItem Parser::parse( const std::string & str )
{
	auto pos = str.find( s_delimiter );
	return SettingsItem( str.substr( 0, pos ), str.substr( pos + 1, str.npos ) );
}

std::string Parser::pack( const SettingsItem & line )
{
	return line.m_key + "=" + line.m_value;
}
