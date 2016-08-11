#pragma once

#include "TKinematicScheme.h"

namespace pss
{
	class TKinematicSchemeBuilder
	{

	private:
		TKinematicScheme						creatKinematicScheme( const core::TCode & code, const core::TK & k );
	public:
		void									buildSchemes();
	};
}