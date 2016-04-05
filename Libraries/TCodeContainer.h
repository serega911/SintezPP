#pragma once
#include <vector>
#include "../Libraries/TCode.h"

namespace pss{
	class TCodeContainer
	{
	private:
		std::vector<TCode>						m_container;
	public:
		void									add(const TCode& code);
		bool									findIn(TCode& code);
	};

}