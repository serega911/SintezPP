#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Cordinate.h"

NS_ARI_START

class Display
{
private:

	void cursorPositionSet( const Cordinate & cord ) const;

public:

	Display();
	~Display();

	void										print(const Cordinate& cord, const char c) const;
};

NS_ARI_END