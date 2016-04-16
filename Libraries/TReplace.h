#pragma once
#include <vector>

namespace pss
{
	class TReplace
	{
	private:
		std::vector<int>						m_container;

	public:
		void									init(int count);
		bool									nextReplace(int maxValue);
		const std::vector<int>&					getReplace() const;
		int										operator[](int i) const;
		int										size() const;


	};
}