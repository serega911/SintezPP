#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"

NS_ARI_START

class DefK
	: public NS_CORE ApplicationBase
{
private:

	void										readInitialData() override;
	

public:

	void										calcExample();
	void										run() override;

};

NS_ARI_END