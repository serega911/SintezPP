#pragma once
#include <map>
#include <vector>
#include "../Libraries/TCode.h"

namespace pss{
	class TCodeContainer
	{
	private:
		std::map<int, std::map<int, std::vector<TCode>>>	m_container;
	public:
		void									add(const TCode& code);
		bool									findIn(const TCode& code) const;
	};

}