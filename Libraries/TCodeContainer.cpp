#include "../Libraries/TCodeContainer.h"

void pss::TCodeContainer::add(const TCode& code)
{
	auto& container = m_container[code.getChains()[0][0]][code.getChains()[1][0]];
	container.push_back(code);
}

bool pss::TCodeContainer::findIn(const TCode& code) const
{
	//auto& container = m_container[code.getChains()[0][0]][code.getChains()[0][1]];
	auto it1 = m_container.find(code.getChains()[0][0]);
	if (it1 != m_container.end())
	{
		auto it2 = it1->second.find(code.getChains()[1][0]);
		if (it2 != it1->second.end())
		{
			const auto& container = it2->second;
			for (int i = 0; i < container.size(); i++)
			{
				if (code.getChains() == container[i].getChains())
					return true;
			}
		}
	}
		
	
	
		
	return false;
}
