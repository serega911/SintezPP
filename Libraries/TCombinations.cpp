#include "../Libraries/TCombinations.h"

void pss::TCombinations::init(int count)
{
	m_container.clear();
	for (int i = 0; i < count; i++) // RK: use reserve and fill sequence method!
		m_container.push_back(i);
}

bool pss::TCombinations::nextReplace(int maxValue)
{
	if (m_container.size() == 0)  return false;
	std::vector<int>tmp;
	int m = m_container.size(); // RK: empty lines for logic blocks?
	tmp = m_container;
	int x = 1;
	if (tmp[m - 1] < maxValue)
		tmp[m - 1]++;
	else{
		if (m == 1) return false;
		for (int i = 1; i < m; i++)
		if (tmp[i] > i + maxValue - m){
			x = i;
			break;
		}
		tmp[x - 1]++;
		for (int i = x; i < m; i++)
			tmp[i] = tmp[i - 1] + 1;
	}
	if (tmp[0] > maxValue - m + 1){
		return false;
	}
	m_container = tmp;
	return true;
}

const std::vector<int>& pss::TCombinations::getReplace() const
{
	return m_container;
}

int pss::TCombinations::size() const
{
	return m_container.size();
}

int pss::TCombinations::operator[](int i) const
{
	return m_container.at(i);
}
