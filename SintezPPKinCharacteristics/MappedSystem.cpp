#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"

#include "MappedSystem.h"

NS_ARI_USING

ari::MappedSystem_p ari::MappedSystem::create( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k )
{
	return MappedSystem_p( new MappedSystem( chains, k ) );
}

ari::MappedSystem::MappedSystem( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k )
{
	const auto n = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	m_system.clear();
	m_system.resize( chains.size() + n * 2 + 1);
	
	int i;
	for ( i = 0; i < n; i++ )
	{
		m_system[2 * i][NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
		m_system[2 * i][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
		m_system[2 * i][NS_CORE Element( NS_CORE eMainElement::CARRIER, NS_CORE GearSetNumber( i + 1 ) )] = 1;

		m_system[2 * i + 1][NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
		m_system[2 * i + 1][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = k[i].getValue();
	}
	i *= 2;
	for ( const auto& chain : chains )
	{
		for ( const auto& elem : chain.getElements() )
		{
			m_system[i][elem] = 1;
			m_solution[elem] = 0;
		}

		i++;
	}

	m_system[i][NS_CORE Element::INPUT] = 1;
	m_system[i][NS_CORE Element::EMPTY] = 1000;	// Riht parts
	m_solution[NS_CORE Element::EMPTY] = 0;
}

MappedSystem::Matrix ari::MappedSystem::getMatrix()
{
	Matrix ret;

	const auto n = m_system.size();

	NS_CORE Log::warning( n + 1 != m_solution.size(), "Wrong matrix size", NS_CORE Log::CRITICAL, HERE );

	ret.resize( n );

	for ( int i = 0; i < n; i++ )
	{
		ret[i].resize( n + 1 );

		int j = 0;
		for ( const auto& elem : m_solution )
		{
			if ( elem.first != NS_CORE Element::EMPTY )
			{
				ret[i][j] = m_system[i][elem.first];
				j++;
			}
		}
		ret[i][j] = m_system[i][NS_CORE Element::EMPTY];
	}

	return ret;

}

void ari::MappedSystem::setSolution( const std::vector<value>& solution )
{
	int i = 0;
	for ( auto& elem : m_solution )
	{
		if ( elem.first != NS_CORE Element::EMPTY )
		{
			elem.second = solution[i];
			i++;
		}
	}
}
