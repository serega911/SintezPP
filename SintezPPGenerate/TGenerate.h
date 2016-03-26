#pragma once

#include <vector>

namespace pss
{
	class TGenerate
	{
	private:
		std::vector<int>						m_allLinks;
		std::vector<std::vector<std::vector<int>>> m_existingSchemes;	//	Все цепочки связей

		void									generateInOut();
		bool									generateLinks(pss::TCode & code);
		bool									generateFrictions(pss::TCode & code);
		bool									generateBrakes(pss::TCode & code);

		std::vector<std::vector<int>>			create_Chains(int in, int out, const std::vector<int> &links);
		std::vector<int>						create_Vect_BF(std::vector<std::vector<int>> Chains);
	public:
		void									generate();
		


	};
}