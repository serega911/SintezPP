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

const TChainArray& TGearBox::getChains() const
{
	TLog::warning( m_chains.size() == 0, "There is no chains!", TLog::CRITICAL, "TGearBox::getChains()" );
	return m_chains;
}



void TGearBox::makeChains( TChainArray &chains ) const
{
	//поиск цепочек связей
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		for ( size_t j = 0; j < chains.size(); j++ )
		{
			if ( j != i && chains[i].intersect( chains[j] ) )
			{
				chains[i].addChainToChain( chains[j] );
				chains[j].clear();
			}
		}
	}
	//удаление пустых цепочек
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		if ( chains[i].size() == 0 )
		{
			chains.erase( chains.begin() + i );
			i = i - 1;
		}
	}
	//упорядочиваем
	std::sort( chains.begin(), chains.end() );
}

TChainArray TGearBox::getChainsForCurrentGear() const
{
	auto chains = getChains();
	auto drivingElements = m_gearChanger.getDrivingElementsForGear();

	chains.resize( chains.size() + drivingElements.size() );

	for ( size_t i = 0; i < drivingElements.size(); i++ )
		chains[chains.size() - i - 1].addLinkToChain( drivingElements[i] );

	makeChains( chains );

	return chains;
}

bool TGearBox::createChains()
 {
	 const auto& code = m_code.getCode();

	//Создаем начальные цепочки (каждая связь делается цепочкой)
	const auto size = TSingletons::getInstance()->getGeneralData()._numberOfLinks + 2;

	if ( size > code.size() )
		return false;

	m_chains.clear();
	m_chains.resize(size); 
	for ( size_t i = 0; i < size; i++ ){
		m_chains[i].addLinkToChain(code[i]);
	}

	//поиск элементов, свободных от связей и создание цепочек, которые их содержат
	const TGearSetNumber N (TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears);
	auto in = code[0].getElem1();
	auto out = code[1].getElem1();
	
	for ( const auto& elem : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
	{
		for ( TGearSetNumber i(1); i <= N; i++ )
		{
			size_t b = 0;
			TElement element( elem, i );
			for ( size_t j = 0; j < size; j++ )
			{
				if ( element == code[j].getElem1() || element == code[j].getElem2() )
				{
					b++;
					break;
				}
			}
			if ( b == 0 && element != in && element != out )
			{
				m_chains.emplace_back( element );
			}
		}
	}
	//поиск цепочек связей, удаление пустых цепочек
	makeChains( m_chains );

	return true;
}

bool core::TGearBox::turnOnNextGear()
{
	return m_gearChanger.next();
}

