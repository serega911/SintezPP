#include "TCode.h"
#include "func_lib.h"
#include <iostream>

using namespace pss;

TCode::TCode(int w, int n)
{
	m_w = w;
	m_numberOfPlanetaryGears = n;
	m_numberOfBrakes = 0;
	m_numberOfFrictions = 0;
	m_numberOfLinks = 0;
	//	Резервируем место для элементов входа и выхода
	m_codeSize = 2;
	m_code.push_back(0);
	m_code.push_back(0);
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
	if (in / 10 <= 3 && in % 10 <= m_numberOfPlanetaryGears && in > 9)
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
	if (out / 10 <= 3 && out % 10 <= m_numberOfPlanetaryGears && out>9)
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
		if (links[i] / 1000>3 || links[i] / 100 % 10>m_numberOfPlanetaryGears || links[i] % 100 / 10>3 || links[i] % 10 > m_numberOfPlanetaryGears)
		{
			pss::SetColor(15, 4);
			std::cout << "Установка связей не удалась!\nПричина сбоя: " << links[i] << ". Вектор кода остался без изменений.";
			print();
			pss::SetColor(15, 0);
			system("pause");
			return false;
		}
	if (m_numberOfLinks != 0)
	{
		m_code.erase(m_code.begin()+2,m_code.begin()+m_numberOfLinks+2);
	}
	m_numberOfLinks = links.size();
	m_code.insert(m_code.begin()+2,links.begin(), links.end());
	m_codeSize = m_code.size();
	return true;
}

bool TCode::setFrictions(std::vector<int> frict)
{
	for (int i = 0; i < frict.size(); i++)
		if (frict[i] / 1000>3 || frict[i] / 100 % 10 > m_numberOfPlanetaryGears || frict[i] % 100 / 10>3 || frict[i] % 10 > m_numberOfPlanetaryGears)
		{
			pss::SetColor(15, 4);
			std::cout << "Установка фрикционов не удалась!\nПричина сбоя: " << frict[i] << ". Вектор кода остался без изменений.";
			print();
			pss::SetColor(15, 0);
			system("pause");
			return false;
		}
	if (m_numberOfFrictions != 0)
	{
		m_code.erase(m_code.begin()+2+m_numberOfLinks,m_code.begin()+2+m_numberOfLinks+m_numberOfFrictions);
	}
	m_numberOfFrictions = frict.size();
	m_code.insert(m_code.begin()+2+m_numberOfLinks,frict.begin(), frict.end());
	m_codeSize = m_code.size();
	return true;
}

bool TCode::setBrakes(std::vector<int> brakes)
{
	for (int i = 0; i < brakes.size(); i++)
	{
		if (brakes[i] / 10>3 || brakes[i] % 10 > m_numberOfPlanetaryGears || brakes[i] < 10)
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
	if (m_numberOfBrakes != 0)
	{
		m_code.erase(m_code.begin()+2+m_numberOfLinks+m_numberOfFrictions,m_code.begin()+2+m_numberOfLinks+m_numberOfFrictions+m_numberOfBrakes);
	}
	m_numberOfBrakes = brakes.size();
	m_code.insert(m_code.begin()+2+m_numberOfLinks+m_numberOfFrictions,brakes.begin(), brakes.end());
	m_codeSize = m_code.size();
	return true;
}

void TCode::print() const
{
	std::cout << std::endl << std::endl;
	pss::SetColor(15, 2);
	std::cout << "==================================================\n";
	pss::SetColor(15, 0);
	std::cout << "Длина вектора кода:			" << m_codeSize << std::endl;
	std::cout << "Число степеней свободы:			" << m_w << std::endl;
	std::cout << "Количество планетарных механизмов:	" << m_numberOfPlanetaryGears << std::endl;
	std::cout << "--------------------------------------------------\n";
	std::cout << "Количество связей:			" << m_numberOfLinks << std::endl;
	std::cout << "Количество фрикционов:			" << m_numberOfFrictions << std::endl;
	std::cout << "Количество тормозов:			" << m_numberOfBrakes << std::endl;
	std::cout << "--------------------------------------------------\n";
	for (int i=0; i < m_codeSize; i++)
	{
		if (i == 1 || i == 2 || i == 2+m_numberOfLinks || i == 2+m_numberOfLinks+m_numberOfFrictions)
			std::cout << "| "; 
		std::cout << m_code[i] << ' ';
	}
	std::cout << "\n--------------------------------------------------\n";
}

void TCode::clear()
{
	m_numberOfLinks=m_numberOfFrictions=m_numberOfBrakes=0;
	m_code.clear();
	m_code.push_back(0);
	m_code.push_back(0);
	m_codeSize = m_code.size();;
}

int TCode::size() const
{
	return m_codeSize;
}

int TCode::getNumberOfPlanetaryGears() const
{
	return m_numberOfPlanetaryGears;
}

int TCode::getW() const
{
	return m_w;
}

int TCode::getNumberOfLinks() const
{
	return m_numberOfLinks;
}

int TCode::getNumberOfFrictions() const
{
	return m_numberOfFrictions;
}

int TCode::getNumberOfBrakes() const
{
	return m_numberOfBrakes;
}

void TCode::writeCodeToFile(std::ofstream& file) const
{
	for (int i=0; i < m_codeSize; i++)
		file << m_code[i] << ' ';
	file << '\n';
}

void TCode::writeParametersToFile(std::ofstream& file) const
{
	file << m_w << ' ' << m_numberOfPlanetaryGears << ' ' << m_numberOfLinks << ' ' << m_numberOfFrictions << ' ' << m_numberOfBrakes << '\n';
}

void TCode::loadCodeFromFile(std::ifstream& file)
{
	m_codeSize = 2 + m_numberOfLinks + m_numberOfFrictions + m_numberOfBrakes;
	m_code.resize(m_codeSize);
	for (auto& it : m_code)
		file >> it;
}

void TCode::loadParametersFromFile(std::ifstream& file)
{
	file >> m_w >> m_numberOfPlanetaryGears >> m_numberOfLinks >> m_numberOfFrictions >> m_numberOfBrakes;
}

bool TCode::check() const
{
	for (int i = 0; i < 3 * m_numberOfPlanetaryGears; i++)
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
