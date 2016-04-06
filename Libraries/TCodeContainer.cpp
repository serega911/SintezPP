#include "../Libraries/TCodeContainer.h"

void pss::TCodeContainer::add(const TCode& code)
{
	m_container.insert(code);
}

bool pss::TCodeContainer::findIn(const TCode& code) const
{
	if (m_container.find(code) != m_container.end())
	{
		return true;
	}	
	return false;
}

void pss::TCodeContainer::writeToFile(std::ofstream&) const
{

}

void pss::TCodeContainer::loadFromFile(std::ifstream&)
{

}

int pss::TCodeContainer::size() const
{
	return m_container.size();
}
