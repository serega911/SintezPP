#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "GlobalDefines.h"
#include "IIOItem.h"

NS_CORE_START

class Now: public IIOItem
{
private:

	std::string									m_message;

public:

	static const Now START_TIME;
	static const Now FINISH_TIME;

	Now(const std::string &message);

	void								writeToFile(std::ostream& file) const override;
	bool								loadFromFile(std::istream& file) override;
};

NS_CORE_END
