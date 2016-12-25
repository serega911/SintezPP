#include "SettingsItem.h"
#include "Parser.h"

NS_CORE_USING

SettingsItem::SettingsItem( const std::string & key, const std::string & val )
	:m_value( val ), m_key( key )
{

}

core::SettingsItem::SettingsItem( const std::string & line )
{
	*this = Parser::parse( line );
}

const std::string& SettingsItem::getValue() const
{
	return m_value;
}

const std::string& SettingsItem::getKey() const
{
	return m_key;
}

SettingsItem::SettingsItem()
	: SettingsItem( "", "" )
{

}

bool SettingsItem::loadFromFile( std::istream& file )
{
	if ( file.eof() )
		return false;

	std::string buf;
	file >> buf;
	*this = Parser::parse(buf);
	return true;
}

void SettingsItem::writeToFile( std::ostream& file ) const
{
	file << Parser::pack( *this );
}
