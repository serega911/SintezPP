#include "../Libraries/TK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>


pss::TK::TK(float beginNegative, float endNegative, float beginPositive, float endPositive, float dK) :
m_beginNegative(beginNegative), m_endNegative(endNegative), m_beginPositive(beginPositive), m_endPositive(endPositive), m_dK(dK), m_isFinded(false)
{
	if (m_beginNegative <= -4.5f && m_endNegative >= -4.5f)
		m_midNegative = -4.5f;
	else
		m_midNegative = (m_beginNegative + m_endNegative) / 2.0f;
	if (m_beginPositive <= 4.5f && m_endPositive >= 4.5f)
		m_midPositive = 4.5f;
	else
		m_midPositive = (m_beginPositive + m_endPositive) / 2.0f;


	m_K.resize(pss::TSingletons::getInstance()->getNumberOfPlanetaryGears());
	for (auto& it : m_K)
		it = m_midNegative;
	m_KInterval.resize(pss::TSingletons::getInstance()->getNumberOfPlanetaryGears());
	for (auto& it : m_KInterval)
		it = eInterval::MID_NEGATIVE;
}

const float pss::TK::operator[](int i) const
{
	return m_K.at(i);
}

bool pss::TK::next()
{
	int k = (int)m_K.size();
	for (int i = k - 1; i >= 0; --i)
	{
		if (m_K[i] > m_midNegative - m_dK  && m_KInterval[i] == eInterval::BEG_NEGATIVE)
		{
			m_K[i] = m_midNegative;
			m_KInterval[i] = eInterval::MID_NEGATIVE;
		}
		else
		{
			m_K[i] += m_dK;
			if (m_K[i] > m_endNegative && m_KInterval[i] == eInterval::MID_NEGATIVE)
			{
				m_K[i] = m_beginPositive;
				m_KInterval[i] = eInterval::BEG_POSITIVE;
			}
			if (m_K[i] > m_midPositive && m_KInterval[i] == eInterval::BEG_POSITIVE)
			{
				m_K[i] = m_midPositive;
				m_KInterval[i] = eInterval::MID_POSITIVE;
			}
			if (m_K[i] > m_endPositive && m_KInterval[i] == eInterval::MID_POSITIVE)
			{
				m_K[i] = m_beginNegative;
				m_KInterval[i] = eInterval::BEG_NEGATIVE;
			}
			return true;
		}
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


