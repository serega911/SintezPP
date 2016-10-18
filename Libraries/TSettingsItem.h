#pragma once

#include <string>
#include "GlobalDefines.h"
#include "TParser_fwd.h"
#include "IIOItem.h"

NS_CORE_START

class TSettingsItem : public IIOItem
{
private:

	friend class TParser;

	std::string									m_value;
	std::string									m_key;

public:

	TSettingsItem( const std::string & key, const std::string & val );
	TSettingsItem();

	virtual void								writeToFile( std::ostream& file ) const override;
	virtual bool								loadFromFile( std::istream& file ) override;

	const std::string&							getKey() const;
	const std::string&							getValue() const;

};

NS_CORE_END