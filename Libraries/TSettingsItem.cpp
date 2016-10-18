#include "TSettingsItem.h"
#include "TParser.h"

NS_CORE_USING

TSettingsItem::TSettingsItem( const std::string & key, const std::string & val )
	:m_value( val ), m_key( key )
{

}

const std::string& core::TSettingsItem::getValue() const
{
	return m_value;
}

const std::string& core::TSettingsItem::getKey() const
{
	return m_key;
}

core::TSettingsItem::TSettingsItem()
	: TSettingsItem( "", "" )
{

}

bool core::TSettingsItem::loadFromFile( std::istream& file )
{
	std::string buf;
	file >> buf;
	*this = TParser::parse(buf);
	return !file.eof();
}

void core::TSettingsItem::writeToFile( std::ostream& file ) const
{
	file << TParser::pack( *this );
}
