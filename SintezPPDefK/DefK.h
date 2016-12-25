#pragma once

#include <vector>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"

NS_ARI_START

class DefK
	: public NS_CORE ApplicationBase
{
private:	

public:

	struct UISpecialData
	{
		std::vector<std::pair<float, float>>	_ranges;
		std::vector<float>						_i;
	};

	void										readUISpecialData();
	void										setUISpecialData( const UISpecialData& data );

	void										calcExample();
	void										run() override;

};

NS_ARI_END