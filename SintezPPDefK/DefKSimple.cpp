#include <algorithm>

#include "CheckAllPossibilities.h"
#include "DefKSimple.h"
#include "Equations.h"
#include "GearBox.h"
#include "../Libraries/Singletons.h"

NS_ARI_USING

ari::DefKSimple::DefKSimple()
{
}

NS_CORE InternalGearRatioArray	 DefKSimple::calculate( const NS_CORE Code& code )
{

	const auto size = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	const NS_CORE InternalGearRatios initial( size );
	NS_CORE InternalGearRatioArray	 ans;

	auto calcFunc = [&]( const NS_CORE Ratios& curI ) -> bool
	{
		NS_CORE InternalGearRatios k = findK( code, initial, curI );
		 
		if ( k.size() != 0 )
		{
			ans.emplace_back( k );
		}

		return true;// !k.check();
	};
	
	CheckAllPossibilities::checkAllRatiosPermutations( calcFunc );

	return ans;
}

NS_CORE InternalGearRatios DefKSimple::findK( const NS_CORE Code& code, const NS_CORE InternalGearRatios& initialKValues, const NS_CORE Ratios& iTarget )
{
	System system;
	system.init( initialKValues );

	GearBox gb( code );
	gb.createChains();

	int i = 0;
	do
	{
		if ( iTarget[i] != NS_CORE RatioValue( 0.0 ) )
			if ( !system.addGearChains( gb.getChainsForCurrentGear(), NS_CORE GearNumber( i + 1 ), iTarget[i] ) )
				return NS_CORE InternalGearRatios();
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


NS_CORE InternalGearRatios DefKSimple::solveSimple( System& system )
{
	const auto& initialData = NS_CORE Singletons::getInstance()->getInitialData();
	const auto countOfEquations = initialData._realNumberOfGears * initialData._numberOfPlanetaryGears;
	auto& unknowns = system.getUnknownVariables();
	int solvedCount = 0;

	do
	{
		solvedCount = 0;
		for ( size_t i = 0; i < initialData._realNumberOfGears; i++ )
		{
			for ( size_t j = 0; j < initialData._numberOfPlanetaryGears; j++ )
			{
				auto& gearSetVariables = system.getVariablesSet( NS_CORE GearNumber( i ), j );
				const auto undefElements = findOneUndefElem( gearSetVariables );
				//если неизвестное одно - можем его найти
				if ( undefElements.size() == 1 )
				{
					solvedCount++;
					VariableValue value = Equations::calcOne( undefElements[0], gearSetVariables );

					//отмечаем как известное
					for ( auto& unknown : unknowns )
						if ( unknown.findElementInListeners( NS_CORE Element( undefElements[0], NS_CORE GearSetNumber(j + 1) ), NS_CORE GearNumber( i + 1 ) ) )
							unknown.setLastValue( value );

					//проверяем всё ли мы нашли
					if ( isAllKValuesFinded( system ) )
						return geInternalGearRatioValuesFromSystem( system );
				}
			}
		}
	} while ( solvedCount != 0 );

	if ( isAllKValuesFinded( system ) )
		return geInternalGearRatioValuesFromSystem( system );
	else
		return NS_CORE InternalGearRatios();

}

NS_CORE InternalGearRatios DefKSimple::geInternalGearRatioValuesFromSystem( const System & system )
{
	const auto& initialData = NS_CORE Singletons::getInstance()->getInitialData();

	NS_CORE InternalGearRatioValueArray kValues;
	for ( size_t i = 0; i < initialData._numberOfPlanetaryGears; i++ )
	{
		if ( system.getUnknownVariables()[i].getIsDefined() )
			kValues.push_back( NS_CORE InternalGearRatioValue( system.getUnknownVariables()[i].getValue() ) );
		else
		{
			kValues.clear();
			break;
		}
	}

	NS_CORE InternalGearRatios ret( kValues );

	return ret;
}

bool ari::DefKSimple::isAllKValuesFinded( const System & system )
{
	const auto& initialData = NS_CORE Singletons::getInstance()->getInitialData();

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
			auto& gearSetVariables = system.getVariablesSet( NS_CORE GearNumber( i ), j );
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
