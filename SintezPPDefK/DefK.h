#pragma once


#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"

NS_ARI_START

class DefK
	: public NS_CORE ApplicationBase
{
private:

public:

	void										calcExample();
	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END