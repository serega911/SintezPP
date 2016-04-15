#include "../Libraries/TCode.h"
#include "func_lib.h"
#include "../Libraries/TSingletons.h"
#include <iostream>
#include <algorithm>

using namespace pss;

TCode::TCode()
{
	clear();
}

TCode::~TCode(void)
{
}

TLink TCode::operator[](int i) const
{
	return m_code.at(i);
}

void TCode::setIn(const TElement & in)
{
	m_code[0].set(in, TElement::INPUT);
}

void TCode::setOut(const TElement & out)
{
	m_code[1].set(out, TElement::OUTPUT);
}

void TCode::setLinks(const std::vector<TLink>& links)
{
	if (m_links)
	{
		m_code.erase(m_code.begin() + 2, m_code.begin() + m_links + 2);	
	}
	m_code.insert(m_code.begin()+2,links.begin(), links.end());
	m_links = links.size();
	createChains();
}

void TCode::setFrictions(const std::vector<TLink>& frictions)
{
	if (m_frictions)
	{
		m_code.erase(m_code.begin() + 2 + m_links, m_code.begin() + 2 + m_links + m_frictions);
	}
	m_code.insert(m_code.begin() + 2 + m_links, frictions.begin(), frictions.end());
	m_frictions = frictions.size();
}

void TCode::setBrakes(const std::vector<TLink>& brakes)
{
	if (m_brakes)
	{
		m_code.erase(m_code.begin() + 2 + m_links + m_frictions, m_code.begin() + 2 + m_links + m_frictions + m_brakes);
	}
	m_code.insert(m_code.begin() + 2 + m_links + m_frictions, brakes.begin(), brakes.end());
	m_brakes = brakes.size();
}

void TCode::print() const
{
	std::cout << std::endl << std::endl;
	pss::SetColor(15, 2);
	std::cout << "==================================================\n";
	pss::SetColor(15, 0);
	std::cout << "Длина вектора кода:			" << m_code.size() << std::endl;
	std::cout << "--------------------------------------------------\n";
	for (int i = 0; i < m_code.size(); i++)
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
	m_code.resize(2);
	m_chains.clear();
	m_links = 0;
	m_frictions = 0;
	m_brakes = 0;
}

int TCode::size() const
{
	return m_code.size();
}


void TCode::writeToFile(std::ofstream& file) const
{
	for (int i = 0; i < m_code.size(); i++)
		file << m_code[i] << ' ';
	file << '\n';
}

void TCode::loadFromFile(std::ifstream& file)
{
	auto codeSize = 2 + pss::TSingletons::getInstance()->getNumberOfLinks() + pss::TSingletons::getInstance()->getNumberOfFrictions() + pss::TSingletons::getInstance()->getNumberOfBrakes();
	m_code.resize(codeSize);
	for (auto& it : m_code)
	{
		int num;
		file >> num;
		int elem1 = num / 100;
		int elem2 = num % 100;
		it.set(pss::TElement(pss::TMainElement(pss::TMainElement::eMainElements(elem1 / 10)), elem1 % 10), pss::TElement(pss::TMainElement(pss::TMainElement::eMainElements(elem2 / 10)), elem2 % 10));
	}
}

bool TCode::checkFree() const
{
	for (int i = 0; i < 3 * pss::TSingletons::getInstance()->getNumberOfPlanetaryGears(); i++)
	{
		int count = 0;
		for (int j = 0; j < m_code.size(); j++)
			if (i == m_code[j].getElem1().getSerialNumber() || i == m_code[j].getElem2().getSerialNumber())
				count++;
		if (count == 0)
			return false;
	}
	return true;
}	//проверяет остались ли пустые элементы

const std::vector<TLink>& TCode::getCode() const
{
	return m_code;
}

TLink pss::TCode::getIn() const
{
	return m_code[0];
}

TLink pss::TCode::getOut() const
{
	return m_code[1];
}

const std::vector<TChain>& pss::TCode::getChains() const
{
	return m_chains;
}

void pss::TCode::createChains()
{
	//Создаем начальные цепочки (каждая связь делается цепочкой)
	m_chains.clear();
	int size = pss::TSingletons::getInstance()->getNumberOfLinks() + 2;
	m_chains.resize(size);

	for (int i = 0; i < m_chains.size(); i++){
		m_chains[i].addLinkToChain(m_code[i]);
	}
	//поиск элементов, свободных от связей и создание цепочек, которые их содержат
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	auto in = m_code[0].getElem1();
	auto out = m_code[1].getElem1();
	for (size_t i = 1; i <= N; i++)
	{
		for (pss::TMainElement elem; elem.end(); elem++)
		{
			size_t b = 0;
			for (size_t j = 0; j < size; j++){
				if (pss::TElement(elem, i) == m_code[j].getElem1() || pss::TElement(elem, i) == m_code[j].getElem2())
				{
					b++;
				}
			}
			if (b == 0 && pss::TElement(elem, i) != in && pss::TElement(elem, i) != out){
				m_chains.resize(m_chains.size() + 1);
				m_chains[m_chains.size() - 1].addElementToChain(pss::TElement(elem, i));
				b = 0;
			}
		}
	}
	//поиск цепочек связей
	for (size_t i = 0; i < m_chains.size() - 1; i++){
		for (size_t j = i + 1; j < m_chains.size(); j++){
			if (m_chains[i].intersect(m_chains[j]))
			{
				m_chains[i].addChainToChain(m_chains[j]);
				m_chains[j].clear();
			}
		}
	}
	//удаление пустых цепочек
	for (size_t i = 0; i < m_chains.size(); i++){
		if (m_chains[i].size() == 0){
			m_chains.erase(m_chains.begin() + i);
			i = i - 1;
		}
	}
	std::sort(m_chains.begin(), m_chains.end());
}

bool pss::TCode::check() const
{
	auto N = pss::TSingletons::getInstance()->getNumberOfPlanetaryGears();
	//проверки корректности кода
	for (size_t i = 0; i < m_chains.size(); i++)
	{
		//проверка связи вход-выход
		if (m_chains[i].find(TElement::INPUT) && m_chains[i].find(TElement::OUTPUT))
		{
			//std::cout << "Есть связь входа с выходом:\n";
			return false;
		}
		//проверка связей между элементами одного ряда
		if (!m_chains[i].checkElemByOnePlanetarySet())
		{
			//std::cout << "Есть связь между элементами одного ряда:\n";
			return false;
		}
	}
	return true;
}

const std::vector<TElement> pss::TCode::getElementsForFrictions() const
{
	std::vector<TElement> vect;
	for (int i = 0; i < m_chains.size(); i++)
	{
		vect.push_back(m_chains[i].getFirst());
	}
	return vect;
}

const std::vector<TElement> pss::TCode::getElementsForBrakes() const
{
	std::vector<TElement> vect;
	for (int i = 0; i < m_chains.size(); i++)
	{
		if (!m_chains[i].find(TElement::INPUT) && !m_chains[i].find(TElement::OUTPUT))
		{
			vect.push_back(m_chains[i].getFirst());
		}
	}
	return vect;
}

bool pss::operator<(const TCode& code1, const TCode& code2)
{
	return code1.getChains() < code2.getChains();
}