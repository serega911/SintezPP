#pragma once

#include "Fumction.h"

namespace pss
{
	class WSet
	{
	private:
		struct Var
		{
			variable*	_var = nullptr;
			bool		_def = false;
		};
		Var										m_set[4];	// k, w1, w2, w3
	public:
		Var&									operator[]( size_t i );
	};

}