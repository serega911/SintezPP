#include "../Libraries/TK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>
#include <algorithm>


pss::TK::TK(double begin, double end, double dK)
{
	m_K.resize(pss::TSingletons::getInstance()->getNumberOfPlanetaryGears());
	m_combi.resize(pss::TSingletons::getInstance()->getNumberOfPlanetaryGears());
	for (int i = 0; i < m_K.size(); i++)
	{
		m_K[i] = begin;
		m_combi[i] = 0;
	}
	pushIntervalToValues(begin, end, dK);
}

pss::TK::TK(double beginNegative, double endNegative, double beginPositive, double endPositive, double dK) :
pss::TK::TK(beginNegative, endNegative, dK)
{
	pushIntervalToValues(beginPositive, endPositive, dK);
}

bool pss::TK::inDia(const double & val)
{
	double a = 2.0f;
	double b = 4.5f;
	return (abs(val) <= b && abs(val) >= 2);
}

void pss::TK::pushIntervalToValues(double beg, double end, double dk)
{
	if (beg * end > 0)
	{
		for (double k = beg; k <= end; k += dk)
			m_kValues.push_back(k);
	}
	std::sort(m_kValues.begin(), m_kValues.end(), 
		[=](const double & x1, const double & x2)->bool
		{
		if (inDia(x1) == inDia(x2))
			return abs(x1) < abs(x2);
		if (inDia(x1))
			return true;
		else 
			return false;
		});
	for (int i = 0; i < m_K.size(); i++)
	{
		m_K[i] = m_kValues[0];
	}
}

const double pss::TK::operator[](int i) const
{
	return m_K.at(i);
}

bool pss::TK::next()
{
	if(pss::next_combination_repetition(m_combi, m_kValues.size()-1, 0))
	{
		for (int i = 0; i < m_combi.size(); i++)
			m_K[i] = m_kValues[m_combi[i]];
		return true;
	}
	return false;
}

void pss::TK::print() const
{
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

