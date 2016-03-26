#include "TCode.h"
#include "func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>

using namespace pss;

TCode::TCode()
{
	clear();
}

TCode::~TCode(void)
{
}

int TCode::operator[](int i) const
{
	if (i<m_codeSize)
		return m_code[i];
	else
		return -1;
}

bool TCode::setIn(int in)
{
	if (in / 10 <= 3 && in % 10 <= pss::TSingletons::getInstance()->getNumberOfPlanetaryGears() && in > 9)
	{
		m_code[0] = 100*in + 44;
		return true;
	}
	pss::SetColor(15, 4);
	std::cout << "Установка элемента входа не удалась!" << std::endl;
	pss::SetColor(15, 0);
	system("pause");
	return false;
}

bool TCode::setOut(int out)
{
	if (out / 10 <= 3 && out % 10 <= pss::TSingletons::getInstance()->getNumberOfPlanetaryGears() && out>9)
	{
		m_code[1] = 100*out + 55;
		return true;
	}
	pss::SetColor(15, 4);
	std::cout << "Установка элемента выхода не удалась!" << std::endl;
	pss::SetColor(15, 0);
	system("pause");
	return false;
}

bool TCode::setLinks(std::vector<int> links)
{
	for (int i = 0; i < links.size(); i++)
		if (links[i] / 1000>3 || links[i] / 100 % 10>pss::TSingletons::getInstance()->getNumberOfPlanetaryGears() || links[i] % 100 / 10>3 || links[i] % 10 > pss::TSingletons::getInstance()->getNumberOfPlanetaryGears())
		{
			pss::SetColor(15, 4);
			std::cout << "Установка связей не удалась!\nПричина сбоя: " << links[i] << ". Вектор кода остался без изменений.";
			print();
			pss::SetColor(15, 0);
			system("pause");
			return false;
		}
	if (m_links)
	{
		m_code.erase(m_code.begin() + 2, m_code.begin() + m_links + 2);	
	}
	m_code.insert(m_code.begin()+2,links.begin(), links.end());
	m_codeSize = m_code.size();
	m_links = links.size();
	return true;
}

bool TCode::setFrictions(std::vector<int> frict)
{
	for (int i = 0; i < frict.size(); i++)
	if (frict[i] / 1000 > 3 || frict[i] / 100 % 10 > pss::TSingletons::getInstance()->getNumberOfPlanetaryGears() || frict[i] % 100 / 10>3 || frict[i] % 10 > pss::TSingletons::getInstance()->getNumberOfPlanetaryGears())
	{
		pss::SetColor(15, 4);
		std::cout << "Установка фрикционов не удалась!\nПричина сбоя: " << frict[i] << ". Вектор кода остался без изменений.";
		print();
		pss::SetColor(15, 0);
		system("pause");
		return false;
	}
	if (m_frictions)
	{
		m_code.erase(m_code.begin() + 2 + m_links, m_code.begin() + 2 + m_links + m_frictions);
	}
	m_code.insert(m_code.begin() + 2 +m_links, frict.begin(), frict.end());
	m_codeSize = m_code.size();
	m_frictions = frict.size();
	return true;
}

bool TCode::setBrakes(std::vector<int> brakes)
{
	for (int i = 0; i < brakes.size(); i++)
	{
		if (brakes[i] / 10>3 || brakes[i] % 10 > pss::TSingletons::getInstance()->getNumberOfPlanetaryGears() || brakes[i] < 10)
		{
			pss::SetColor(15, 4);
			std::cout << "Установка торомозов не удалась!\nПричина сбоя: " << brakes[i] << ". Вектор кода остался без изменений.";
			print();
			pss::SetColor(15, 0);
			system("pause");
			return false;
		}
		brakes[i] = brakes[i]*100 + 66;
	}
	if (m_brekes)
	{
		m_code.erase(m_code.begin() + 2 + m_links + m_frictions, m_code.begin() + 2 + m_links + m_frictions + m_brekes);
	}
	m_code.insert(m_code.begin() + 2 + m_links + m_frictions, brakes.begin(), brakes.end());
	m_codeSize = m_code.size();
	m_brekes = brakes.size();
	return true;
}

void TCode::print() const
{
	std::cout << std::endl << std::endl;
	pss::SetColor(15, 2);
	std::cout << "==================================================\n";
	pss::SetColor(15, 0);
	std::cout << "Длина вектора кода:			" << m_codeSize << std::endl;
	std::cout << "--------------------------------------------------\n";
	for (int i=0; i < m_codeSize; i++)
	{
		if (i == 1 || i == 2 || i == 2 + pss::TSingletons::getInstance()->getNumberOfLinks() || i == 2 + pss::TSingletons::getInstance()->getNumberOfLinks() + pss::TSingletons::getInstance()->getNumberOfFrictions())
			std::cout << "| "; 
		std::cout << m_code[i] << ' ';
	}
	std::cout << "\n--------------------------------------------------\n";
}

void TCode::clear()
{
	m_code.clear();
	m_code.push_back(0);
	m_code.push_back(0);
	m_codeSize = m_code.size();
	m_links = 0;
	m_frictions = 0;
	m_brekes = 0;
}

int TCode::size() const
{
	return m_codeSize;
}


void TCode::writeToFile(std::ofstream& file) const
{
	for (int i=0; i < m_codeSize; i++)
		file << m_code[i] << ' ';
	file << '\n';
}

void TCode::loadFromFile(std::ifstream& file)
{
	m_codeSize = 2 + pss::TSingletons::getInstance()->getNumberOfLinks() + pss::TSingletons::getInstance()->getNumberOfFrictions() + pss::TSingletons::getInstance()->getNumberOfBrakes();
	m_code.resize(m_codeSize);
	for (auto& it : m_code)
		file >> it;
}

bool TCode::check() const
{
	for (int i = 0; i < 3 * pss::TSingletons::getInstance()->getNumberOfPlanetaryGears(); i++)
	{
		int count = 0;
		for (int j = 0; j < m_code.size(); j++)
			if (pss::pos_2_code(i) == m_code[j] / 100 || pss::pos_2_code(i) == m_code[j] % 100)
				count++;
		if (count == 0)
			return false;
	}
	return true;
}

const std::vector<int>& TCode::getCode() const
{
	return m_code;
}
