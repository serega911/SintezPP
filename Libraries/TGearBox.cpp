#include <algorithm>

#include "TGearBox.h"
#include "TSingletons.h"
#include "TLog.h"

NS_CORE_USING

TGearBox::TGearBox( const TCode& code )
	: m_code( code )
	, m_gearChanger( code )
{
}

const TCode& TGearBox::getCode() const
{
	return m_code;
}

TCode& TGearBox::getRefferenceToCode()
{
	return m_code;
}

const TChains& TGearBox::getChains() const
{
	TLog::warning( m_chains.size() == 0, "There is no chains!", TLog::CRITICAL, "TGearBox::getChains()" );
	return m_chains;
}


TChains core::TGearBox::getChainsForCurrentGear() const
{
	auto chains = getChains();
	auto drivingElements = m_gearChanger.getDrivingElementsForGear();

	chains.resize( chains.size() + drivingElements.size() );

	for ( size_t i = 0; i < drivingElements.size(); i++ )
	{
		if ( drivingElements[i].getElem2() == NS_CORE TElement::BRAKE )
		{
			chains[chains.size() - i - 1].addElementToChain( drivingElements[i].getElem1() );
		}
		else
		{
			chains[chains.size() - i - 1].addLinkToChain( drivingElements[i] );
		}
	}

	//поиск цепочек связей
	for ( auto i = 0; i < chains.size() - 1; i++ )
	{
		for ( auto j = i + 1; j < chains.size(); j++ )
		{
			if ( chains[i].intersect( chains[j] ) )
			{
				chains[i].addChainToChain( chains[j] );
				chains[j].clear();
			}
		}
	}
	//удаление пустых цепочек
	for ( auto i = 0; i < chains.size(); i++ )
	{
		if ( chains[i].size() == 0 )
		{
			chains.erase( chains.begin() + i );
			i = i - 1;
		}
	}
	//добавляем тормоза
	for ( auto i = 0; i < drivingElements.size(); i++ )
	{
		if ( drivingElements[i].getElem2() == NS_CORE TElement::BRAKE )
		{
			for ( auto j = 0; j < chains.size(); j++ )
			{
				if ( chains[j].find( drivingElements[i].getElem1() ) )
				{
					chains[j].addElementToChain( NS_CORE TElement::BRAKE );
				}
			}
		}
	}
	std::sort( chains.begin(), chains.end() );
	return chains;
}

bool TGearBox::createChains()
 {
	 const auto& code = m_code.getCode();

	//Создаем начальные цепочки (каждая связь делается цепочкой)
	m_chains.clear();
	auto size = TSingletons::getInstance()->getGeneralData()._numberOfLinks + 2;
	m_chains.resize(size);
	 
	for (auto i = 0; i < m_chains.size(); i++){
		m_chains[i].addLinkToChain(code[i]);
	}
	//поиск элементов, свободных от связей и создание цепочек, которые их содержат
	auto N = TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	auto in = code[0].getElem1();
	auto out = code[1].getElem1();
	for (TGearSetNumber i = 1; i <= N; i++)
	{
		for ( const auto& elem : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
		{
			TCount b = 0;
			for (auto j = 0; j < size; j++){
				if (TElement(elem, i) == code[j].getElem1() || TElement(elem, i) == code[j].getElem2())
				{
					b++;
				}
			}
			if (b == 0 && TElement(elem, i) != in && TElement(elem, i) != out){
				m_chains.resize(m_chains.size() + 1);
				m_chains[m_chains.size() - 1].addElementToChain(TElement(elem, i));
				b = 0;
			}
		}
	}
	//поиск цепочек связей
	for (auto i = 0; i < m_chains.size() - 1; i++){
		for (auto j = i + 1; j < m_chains.size(); j++){
			if (m_chains[i].intersect(m_chains[j]))
			{
				m_chains[i].addChainToChain(m_chains[j]);
				m_chains[j].clear();
			}
		}
	}
	//удаление пустых цепочек
	for (auto i = 0; i < m_chains.size(); i++){
		if (m_chains[i].size() == 0){
			m_chains.erase(m_chains.begin() + i);
			i = i - 1;
		}
	}
	std::sort(m_chains.begin(), m_chains.end());
	return true;
}

bool core::TGearBox::turnOnNextGear()
{
	return m_gearChanger.next();
}

