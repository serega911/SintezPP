#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"

#include "MappedSystem.h"

NS_CORE_USING

MappedSystem_p MappedSystem::createM( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k, const double mIn )
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

		ret->m_system[2 * i + 1][NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = k[i].getValue();
		ret->m_system[2 * i + 1][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
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
	ret->m_system[i][NS_CORE Element::EMPTY] = mIn;	// Riht parts
	ret->m_solution[NS_CORE Element::EMPTY] = 0;

	return ret;
}

NS_CORE MappedSystem::MappedSystem()
{

}

NS_CORE IMappedSystem::Matrix MappedSystem::getMatrix()
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

void MappedSystem::setSolution( const NS_CORE IMappedSystem::Vector& solution )
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

MappedSystem_p MappedSystem::createW( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k, const NS_CORE RatioValue wIn )
{
	MappedSystem_p ret( new MappedSystem );

	const auto n = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	ret->m_system.clear();

	ret->m_system.resize( n );
	for ( int i = 0; i < n; i++ )
	{
		ret->m_system[i][NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = 1;
		ret->m_system[i][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE GearSetNumber( i + 1 ) )] = -k[i].getValue();
		ret->m_system[i][NS_CORE Element( NS_CORE eMainElement::CARRIER, NS_CORE GearSetNumber( i + 1 ) )] = k[i].getValue() - 1;
	}

	std::vector<NS_CORE Element> brakes;

	for ( const auto& chain : chains )
	{
		bool isFirst = true;
		NS_CORE Element prev;
		
		for ( const auto& elem : chain.getElements() )
		{
			if ( elem.getElemN() == NS_CORE eMainElement::BRAKE )
				brakes.emplace_back( elem );

			if ( isFirst )
				isFirst = false;
			else
			{
				Vector equation;
				equation[prev] = 1;
				equation[elem] = -1;
				ret->m_system.push_back( equation );
			}
			prev = elem;
			ret->m_solution[elem] = 0;
		}
		
	}

	Vector inEquation;
	inEquation[NS_CORE Element::INPUT] = 1;
	inEquation[NS_CORE Element::EMPTY] = wIn.getValue();	// Riht parts
	ret->m_system.emplace_back( inEquation );
	ret->m_solution[NS_CORE Element::EMPTY] = 0;

	for ( const auto & brake : brakes )
	{
		Vector equation;
		equation[brake] = 1;
		equation[NS_CORE Element::EMPTY] = 0;	// Riht parts
		ret->m_system.push_back( equation );
	}

	return ret;
}
const MappedSystem::Vector& MappedSystem::getSolution() const
{
	return m_solution;
}
