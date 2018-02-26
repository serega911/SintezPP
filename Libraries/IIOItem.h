#pragma once

#include <iostream>
#include <string>
#include "GlobalDefines.h"

NS_CORE_START

class IIOItem
{
public:
	virtual void								writeToFile( std::ostream& ) const = 0;
	virtual bool								loadFromFile( std::istream& ) = 0;
};

class FakeItem : public IIOItem
{
private:
	std::string									m_str;
public:
	virtual void								writeToFile( std::ostream& file ) const override
	{
		file << m_str;
	}

	virtual bool								loadFromFile( std::istream& file) override
	{
		std::getline(file, m_str);
		if ( m_str == "" )
			std::getline(file, m_str);
		return true;
	}
};

NS_CORE_END
