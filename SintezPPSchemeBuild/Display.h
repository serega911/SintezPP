#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Cordinate.h"

NS_ARI_START

class Display
{
public:
	Display();
	~Display();

	void										print(const Cordinate& cord, const char c);
};

NS_ARI_END