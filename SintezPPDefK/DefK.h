#pragma once

#include <vector>
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/IApplication.h"

NS_ARI_START

class DefK
	: public NS_CORE IApplication
	{
	private:

		void									readInitialData() override;

	public:

		void									run() override;

	};

NS_ARI_END