#pragma once

#include "TKinematicScheme.h"

namespace pss
{
	class TKinematicSchemeBuilder
	{

	private:
		TKinematicScheme						creatKinematicScheme( const pss::TCode & code, const pss::TK & k );
	public:
		void									buildSchemes();
	};
}