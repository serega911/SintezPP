#include "../Libraries/TK.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>
#include <algorithm>


pss::TK::TK(double dK)
{
	m_K.resize(pss::TSingletons::getInstance()->getNumberOfPlanetaryGears());
	m_combi.resize(pss::TSingletons::getInstance()->getNumberOfPlanetaryGears());
	for (int i = 0; i < m_K.size(); i++) // RK: use fill method
	{
		m_combi[i] = 0;
	}
	m_dK = dK;
}

bool pss::TK::inDia(const double & val)
{
	double a = 2.0f;
	double b = 4.5f;
	return (abs(val) <= b && abs(val) >= a);
}

void pss::TK::addInterval(double beg, double end)
{
	if (beg * end > 0)
	{
		for (double k = beg; k <= end; k += m_dK)
			m_kValues.push_back(k);
	}
	std::sort(m_kValues.begin(), m_kValues.end(),  // RK: use empty line for logic block outline
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

void pss::TK::setFinded( const bool finded )
{
	m_isFinded = finded;
}

bool pss::TK::getFinded() const
{
	return m_isFinded;
}

void pss::TK::writeToFile(std::ofstream& file) const
{
	for (auto& it : m_K)
		file << it << ' ';
}

void pss::TK::loadFromFile(std::ifstream&)
{

}

void pss::TK::setValues( const std::vector<double>& values )
{
	m_K = values;
}

