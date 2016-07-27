#include "../Libraries/TCode.h"
#include "func_lib.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TLog.h"
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
	TLog::log( "\n" );
	pss::SetColor(15, 2);
	TLog::log( "==================================================" );
	pss::SetColor(15, 0);
	TLog::log( "Длина вектора кода:			" + std::to_string( m_code.size() ) );
	TLog::log( "--------------------------------------------------" );

	const auto& generalData = pss::TSingletons::getInstance()->getGeneralData();

	for (int i = 0; i < m_code.size(); i++)
	{
		if ( i == 1 || i == 2 || i == 2 + generalData._numberOfLinks || i == 2 + generalData._numberOfLinks + generalData._numberOfFrictions )
			TLog::log( "|", false );
		m_code[i].print();
		TLog::log( " ", false );
	}
	TLog::log( "\n--------------------------------------------------" );
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
	for ( int i = 0; i < m_code.size(); i++ )
		m_code[i].writeTofile( file );
}

void TCode::loadFromFile(std::ifstream& file)
{
	const auto& generalData = pss::TSingletons::getInstance()->getGeneralData();

	auto codeSize = 2 + generalData._numberOfLinks + generalData._numberOfFrictions + generalData._numberOfBrakes;
	m_code.resize(codeSize);

	for (auto& it : m_code)
	{

		it.loadFromFile( file );
	}

	m_links = generalData._numberOfLinks;
	m_frictions = generalData._numberOfFrictions;
	m_brakes = generalData._numberOfBrakes;
}

bool TCode::checkFree() const
{
	for (int i = 0; i < 3 * pss::TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears; i++)
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
	int size = pss::TSingletons::getInstance()->getGeneralData()._numberOfLinks + 2;
	m_chains.resize(size);

	for (int i = 0; i < m_chains.size(); i++){
		m_chains[i].addLinkToChain(m_code[i]);
	}
	//поиск элементов, свободных от связей и создание цепочек, которые их содержат
	auto N = pss::TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	auto in = m_code[0].getElem1();
	auto out = m_code[1].getElem1();
	for (size_t i = 1; i <= N; i++)
	{
		for ( const auto& elem : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
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
	auto N = pss::TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	//проверки корректности кода
	for (size_t i = 0; i < m_chains.size(); i++)
	{
		//проверка связи вход-выход
		if (m_chains[i].find(TElement::INPUT) && m_chains[i].find(TElement::OUTPUT))
		{
			return false;
		}
		//проверка связей между элементами одного ряда
		if (!m_chains[i].checkElemByOnePlanetarySet())
		{
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

std::vector<TLink> pss::TCode::getBrakes() const
{
	std::vector<TLink> ret;

	for ( const auto& it : m_code )
	{
		if ( it.getElem2() == pss::TElement::BRAKE )
			ret.push_back( it );
	}

	return ret;
}

bool pss::operator<(const TCode& code1, const TCode& code2)
{
	return code1.getChains() < code2.getChains();
}