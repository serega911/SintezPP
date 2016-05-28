#pragma once
#include "Fumction.h"
#include <vector>
namespace pss
{

	class Variables
	{
	private:
		struct Var
		{
			variable*	_var = nullptr;
			bool		_def = false;
		};
		typedef  std::vector<Var> varSet;		// k, w1, w2, w3
		static const size_t						s_varSetSize;

		std::vector<varSet>						m_variables;

		void									resize( size_t size );

	public:
		Variables( size_t size );
		varSet &								operator[]( size_t i );
	};
}
