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
	const auto& links = m_code.getLinks();
	const auto in = m_code.getIn();
	const auto out = m_code.getOut();
	const auto linksSize = Singletons::getInstance()->getGeneralData()._numberOfLinks;

	Log::warning( linksSize > links.size(), "Unexpected size!", Log::CRITICAL, HERE );

	//Создаем начальные цепочки (каждая связь делается цепочкой)
	m_chains.clear();
	m_chains.resize( linksSize + 2 );
	m_chains[0].addLinkToChain( in );
	m_chains[1].addLinkToChain( out );
	for ( size_t i = 0; i < linksSize; i++ )
	{
		m_chains[i + 2].addLinkToChain( links[i] );
	}

	//поиск элементов, свободных от связей и создание цепочек, которые их содержат
	const GearSetNumber N( Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears );


	for ( const auto& elem : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
	{
		for ( GearSetNumber i( 1 ); i <= N; ++i )
		{
			size_t b = 0;
			Element element( elem, i );
			for ( size_t j = 0; j < linksSize; j++ )
			{
				if ( element == links[j].getElem1() || element == links[j].getElem2() )
				{
					b++;
					break;
				}
			}
			if ( b == 0 && element != in.getElem1() && element != out.getElem1() )
			{
				m_chains.emplace_back( element );
			}
		}
	}
	//поиск цепочек связей, удаление пустых цепочек
	makeChains( m_chains );
}



