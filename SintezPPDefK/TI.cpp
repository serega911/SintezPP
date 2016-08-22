#include "TI.h"
#include "../Libraries/TSingletons.h"
#include <iostream>

NS_ARI_USING

double TI::m_eps = 0.05;

TI::TI( const NS_CORE TIValueArray& i, double eps )
{
	m_i = i;
	m_eps = eps;
}

TI::TI()
{
}

size_t TI::size() const
{
	return m_i.size();
}

const double TI::operator[](int i) const
{
	return m_i.at(i);
}

void TI::operator=(const TI& obj)
{
	m_i = obj.m_i;
	m_eps = obj.m_eps;
}

void TI::push_back(double value)
{
	m_i.push_back(value);
}

void TI::print()
{
	std::cout << "eps = " << m_eps << std::endl;
	for (auto& it: m_i)
		std::cout << it << ' ';
	std::cout << std::endl;
}

bool TI::findIn( double value ) const
{
	if ( m_i.size() == core::TSingletons::getInstance()->getInitialData()._numberOfGears )
	{
		for ( auto& it : m_i )
		{
			if ( abs( it - value ) <= m_eps )
				return true;
		}
		return false;
	}
	else
		return true;
}

bool TI::operator==( const TI& obj )
{
	if (m_i.size() <= obj.size())
	{
		for (auto& it : m_i)
		{
			bool finded = false;
			for (auto& jt : obj.m_i)
			{
				if (abs(it - jt) <= m_eps)
					finded = true;
			}
			if (finded == false)
				return false;
		}
		return true;
	}
	else
	{
		for (auto& it : obj.m_i)
		{
			bool finded = false;
			for (auto& jt : m_i)
			{
				if (abs(it - jt) <= m_eps)
					finded = true;
			}
			if (finded == false)
				return false;
		}
		return true;
	}
}
