#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"

#include "MappedSystem.h"

NS_ARI_USING

ari::MappedSystem_p ari::MappedSystem::createM( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k )
{
	MappedSystem_p ret( new MappedSystem );

	const auto n = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	ret->m_system.clear();
	ret->m_system.resize( chains.size() + n * 2 + 1 );

	int i;
	for ( i = 0; i < n; i++ )
	{
		ret->m_system[2 * i][NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
		ret->m_system[2 * i][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
		ret->m_system[2 * i][NS_CORE Element( NS_CORE eMainElement::CARRIER, NS_CORE GearSetNumber( i + 1 ) )] = 1;

		ret->m_system[2 * i + 1][NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
		ret->m_system[2 * i + 1][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = k[i].getValue();
	}
	i *= 2;
	for ( const auto& chain : chains )
	{
		for ( const auto& elem : chain.getElements() )
		{
			ret->m_system[i][elem] = 1;
			ret->m_solution[elem] = 0;
		}

		i++;
	}

	ret->m_system[i][NS_CORE Element::INPUT] = 1;
	ret->m_system[i][NS_CORE Element::EMPTY] = 1000;	// Riht parts
	ret->m_solution[NS_CORE Element::EMPTY] = 0;

	return ret;
}

ari::MappedSystem::MappedSystem()
{
	
}

NS_CORE IMappedSystem::Matrix ari::MappedSystem::getMatrix()
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

void ari::MappedSystem::setSolution( const NS_CORE IMappedSystem::Vector& solution )
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

ari::MappedSystem_p ari::MappedSystem::createW( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k )
{
	MappedSystem_p ret( new MappedSystem );

	const auto n = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	ret->m_system.clear();
	ret->m_system.resize( n * 3 + 3);

	int i;
	for ( i = 0; i < n; i++ )
	{
		ret->m_system[i][NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
		ret->m_system[i][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = -k[i].getValue();
		ret->m_system[i][NS_CORE Element( NS_CORE eMainElement::CARRIER, NS_CORE GearSetNumber( i + 1 ) )] = k[i].getValue() - 1;
	}

	for ( const auto& chain : chains )
	{
		bool isFirst = true;
		NS_CORE Element prev;
		for ( const auto& elem : chain.getElements() )
		{
			if ( isFirst )
				isFirst = false;
			else
			{
				ret->m_system[i][prev] = /*( prev == NS_CORE Element::BRAKE ) ? 0 :*/ 1;
				ret->m_system[i][elem] = /*( elem == NS_CORE Element::BRAKE ) ? 0 :*/ -1;
				i++;
			}
			prev = elem;
			ret->m_solution[elem] = 0;
		}
	}

	ret->m_system[i][NS_CORE Element::INPUT] = 1;
	ret->m_system[i][NS_CORE Element::EMPTY] = 100;	// Riht parts
	
	i++;

	ret->m_system[i][NS_CORE Element::BRAKE] = 1;
	ret->m_system[i][NS_CORE Element::EMPTY] = 0;	// Riht parts
	ret->m_solution[NS_CORE Element::EMPTY] = 0;

	return ret;
}

const MappedSystem::Vector& ari::MappedSystem::getSolution() const
{
	return m_solution;
}
