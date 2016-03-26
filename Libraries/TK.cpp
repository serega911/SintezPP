#include "../Libraries/TK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>


pss::TK::TK(float beginNegative, float endNegative, float beginPositive, float endPositive, float dK) :
m_beginNegative(beginNegative), m_endNegative(endNegative), m_beginPositive(beginPositive), m_endPositive(endPositive), m_dK(dK), m_isFinded(false)
{
	m_K.resize(pss::TSingletons::getInstance()->getNumberOfPlanetaryGears());
	for (auto& it : m_K)
		it = beginNegative;
}

const float pss::TK::operator[](int i) const
{
	return m_K.at(i);
}

bool pss::TK::next()
{
	int k = (int)m_K.size();
	for (int i = k - 1; i >= 0; --i)
			if (m_K[i] <= m_endPositive - m_dK)
			{
				m_K[i] += m_dK;
				if (m_K[i] > m_endNegative && m_K[i] < m_beginPositive)
					m_K[i] = m_beginPositive;
				return true;
			}
			else
			{
				m_K[i] = m_beginNegative;
			}
	return false;
}

void pss::TK::print() const
{
	std::cout << std::endl << m_beginNegative << ' ' << m_endNegative << ' ' << m_beginPositive << ' ' << m_endPositive << std::endl << "K: ";
	for (auto &it : m_K)
		std::cout << it << ' ';
	std::cout << std::endl;
	
}

int pss::TK::size() const
{
	return m_K.size();
}

void pss::TK::setFinded()
{
	m_isFinded = true;
}

bool pss::TK::getFinded()
{
	return m_isFinded;
}

void pss::TK::writeToFile(std::ofstream& file) const
{
	for (auto& it : m_K)
		file << it << ' ';
	file << std::endl;
}

void pss::TK::loadFromFile(std::ifstream&)
{

}


