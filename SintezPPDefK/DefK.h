#pragma once

#include <vector>
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/IApplication.h"
#include "../Libraries/TKArray.h"

NS_ARI_START

class DefK
	: public NS_CORE IApplication
	{
	private:

		void									readInitialData() override;
		bool									checkKArray( const NS_CORE TKArray& array );

	public:

		void									run() override;

	};

NS_ARI_END