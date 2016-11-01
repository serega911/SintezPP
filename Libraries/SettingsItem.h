#pragma once

#include <string>
#include "GlobalDefines.h"
#include "Parser_fwd.h"
#include "IIOItem.h"

NS_CORE_START

class SettingsItem : public IIOItem
{
private:

	friend class Parser;

	std::string									m_value;
	std::string									m_key;

public:

	SettingsItem( const std::string & key, const std::string & val );
	SettingsItem();

	virtual void								writeToFile( std::ostream& file ) const override;
	virtual bool								loadFromFile( std::istream& file ) override;

	const std::string&							getKey() const;
	const std::string&							getValue() const;

};

NS_CORE_END