#include <algorithm>

#include "GearBox.h"
#include "Singletons.h"
#include "Log.h"

NS_CORE_USING

GearBox::GearBox( const Code& code )
	: m_code( code )
{
}

const Code& GearBox::getCode() const
{
	return m_code;
}

Code& GearBox::getRefferenceToCode()
{
	return m_code;
}

const ChainArray& GearBox::getChains() const
{
	Log::warning( m_chains.size() == 0, "There is no chains!", Log::CRITICAL, HERE );
	return m_chains;
}

void GearBox::makeChains( ChainArray &chains ) const
{
	const size_t chainsSize = chains.size();
	//поиск цепочек связей
	for ( size_t i = 0; i < chainsSize; i++ )
	{
		for ( size_t j = 0; j < chainsSize; j++ )
		{
			if ( j != i && chains[i].intersect( chains[j] ) )
			{
				chains[i].addChainToChain( chains[j] );
				chains[j].clear();
			}
		}
	}
	//удаление пустых цепочек
	const NS_CORE Chain emptyChain;
	chains.erase( remove( chains.begin(), chains.end(), emptyChain ), chains.end() );
	//упорядочиваем
	std::sort( chains.begin(), chains.end() );
}

void GearBox::createChains()
 {
	const auto& code = m_code.getCode();
	const auto codeSize = Singletons::getInstance()->getGeneralData()._numberOfLinks + 2;

	Log::warning( codeSize > code.size(), "Unexpected size!", Log::CRITICAL, HERE );

	//Создаем начальные цепочки (каждая связь делается цепочкой)
	m_chains.clear();
	m_chains.resize( codeSize );
	for ( size_t i = 0; i < codeSize; i++ )
	{
		m_chains[i].addLinkToChain(code[i]);
	}

	//поиск элементов, свободных от связей и создание цепочек, которые их содержат
	const GearSetNumber N(Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears);
	const auto in = code[0].getElem1();
	const auto out = code[1].getElem1();
	
	for ( const auto& elem : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
	{
		for ( GearSetNumber i(1); i <= N; i++ )
		{
			size_t b = 0;
			Element element( elem, i );
			for ( size_t j = 0; j < codeSize; j++ )
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
}



