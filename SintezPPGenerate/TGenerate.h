#pragma once

#include <vector>
#include "../Libraries/TCode.h"
#include "../Libraries/TLink.h"
#include "../Libraries/TCodeContainer.h"


namespace pss
{
	class TGenerate
	{
	private:
		std::vector<TLink>						m_allLinks;
		pss::TCodeContainer						m_existingSchemes;

		void									generateInOut();
		void									generateLinks(pss::TCode & code);
		void									generateFrictions(pss::TCode & code);
		void									generateBrakes(pss::TCode & code);

		std::vector<std::vector<int>>			create_Chains(int in, int out, const std::vector<int> &links);
		std::vector<int>						create_Vect_BF(std::vector<std::vector<int>> Chains);
	public:
		void									generate();
		


	};
}