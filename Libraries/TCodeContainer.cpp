#include "../Libraries/TCodeContainer.h"

void pss::TCodeContainer::add(const TCode& code)
{
	m_container.push_back(code);
}

bool pss::TCodeContainer::findIn(TCode& code)
{
	for (int i = 0; i < m_container.size(); i++)
	if (code.getChains() == m_container[i].getChains())
		return true;
	return false;
}
