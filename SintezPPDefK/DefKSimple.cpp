#include <algorithm>

#include "CheckAllPossibilities.h"
#include "DefKSimple.h"
#include "Equations.h"
#include "../Libraries/TSingletons.h"

NS_ARI_USING

ari::DefKSimple::DefKSimple()
{
}

NS_CORE TKArray	 DefKSimple::calculate( const NS_CORE TCode& code )
{

	const auto size = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	const NS_CORE TK initial( size );
	NS_CORE TKArray	 ans;

	auto calcFunc = [&]( const NS_CORE TI& curI ) -> bool
	{
		NS_CORE TK k = findK( code, initial, curI );
		 
		if ( k.size() != 0 )
		{
			ans.emplace_back( k );
		}

		return true;
	};
	
	CheckAllPossibilities::checkAllRatiosPermutations( calcFunc );

	return ans;
}

NS_CORE TK DefKSimple::findK( const NS_CORE TCode& code, const NS_CORE TK& initialKValues, const NS_CORE TI& iTarget )
{
	System system;
	system.init( initialKValues );

	NS_CORE TGearBox gb( code );
	gb.createChains();

	int i = 0;
	do
	{
		if ( !system.addGearChains( gb.getChainsForCurrentGear(), NS_CORE TGearNumber( i + 1 ), iTarget[i] ) )
			return NS_CORE TK();
		i++;
	} while ( gb.turnOnNextGear() );

	
	return solveSimple( system );
}

std::vector<NS_CORE eMainElement> findOneUndefElem(const VariablesSet& set)
{
	std::vector<NS_CORE eMainElement> ans;
	
	static const auto elements = { NS_CORE eMainElement::SUN_GEAR, NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE eMainElement::CARRIER, NS_CORE eMainElement::EMPTY };
	ans.reserve( elements.size() );

	//считаем количество неизвестных в уравнении
	for ( const auto & elem : elements )
	{
		if ( set[elem].getDefined() == false )
		{
			ans.emplace_back(elem);
		}
	}

	return ans;
}


NS_CORE TK DefKSimple::solveSimple( System& system )
{
	const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();
	const auto countOfEquations = initialData._numberOfGears * initialData._numberOfPlanetaryGears;
	auto& unknowns = system.getUnknownVariables();
	int solvedCount = 0;

	do
	{
		solvedCount = 0;
		for ( size_t i = 0; i < initialData._numberOfGears; i++ )
		{
			for ( size_t j = 0; j < initialData._numberOfPlanetaryGears; j++ )
			{
				auto& gearSetVariables = system.getVariablesSet( NS_CORE TGearNumber( i ), j );
				const auto undefElements = findOneUndefElem( gearSetVariables );
				//если неизвестное одно - можем его найти
				if ( undefElements.size() == 1 )
				{
					solvedCount++;
					VariableValue value = Equations::calcOne( undefElements[0], gearSetVariables );

					//отмечаем как известное
					for ( auto& unknown : unknowns )
						if ( unknown.findElementInListeners( NS_CORE TElement( undefElements[0], j + 1 ), NS_CORE TGearNumber( i + 1 ) ) )
							unknown.setLastValue( value );

					//проверяем всё ли мы нашли
					if ( isAllKValuesFinded( system ) )
						return getKValuesFromSystem( system );
				}
			}
		}
	} while ( solvedCount != 0 );

	if ( isAllKValuesFinded( system ) )
		return getKValuesFromSystem( system );
	else
		return NS_CORE TK();

}

NS_CORE TK DefKSimple::getKValuesFromSystem( const System & system )
{
	const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();

	NS_CORE TKValueArray kValues;
	for ( size_t i = 0; i < initialData._numberOfPlanetaryGears; i++ )
	{
		if ( system.getUnknownVariables()[i].getIsDefined() )
			kValues.push_back( NS_CORE TKValue( system.getUnknownVariables()[i].getValue() ) );
		else
		{
			kValues.clear();
			break;
		}
	}

	NS_CORE TK ret( kValues );

	return ret;
}

bool ari::DefKSimple::isAllKValuesFinded( const System & system )
{
	const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();

	// check K values
	for ( size_t i = 0; i < initialData._numberOfPlanetaryGears; i++ )
	{
		if ( !system.getUnknownVariables()[i].getIsDefined() )
			return false;
	}

	// check all system
	for ( size_t i = 0; i < initialData._numberOfGears; i++ )
	{
		for ( size_t j = 0; j < initialData._numberOfPlanetaryGears; j++ )
		{
			auto& gearSetVariables = system.getVariablesSet( NS_CORE TGearNumber( i ), j );
			const auto undefElements = findOneUndefElem( gearSetVariables );

			if ( 0 == undefElements.size() )
			{
				if ( !Equations::check( gearSetVariables ) )
					return false;
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}
