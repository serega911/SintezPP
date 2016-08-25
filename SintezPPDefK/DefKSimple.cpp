#include <algorithm>

#include "CheckAllPossibilities.h"
#include "DefKSimple.h"
#include "Equations.h"
#include "../Libraries/TSingletons.h"

NS_ARI_USING

NS_CORE TKArray ari::DefKSimple::calculate( const NS_CORE TCode& code )
{
	NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K_SIMPLE, code );

	const auto size = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	const NS_CORE TK initial( size );
	NS_CORE TKArray ans;

	auto calcFunc = [&]( const NS_CORE TI& curI ) -> bool
	{
		NS_CORE TK k = findK( code, initial, curI );
		 
		if ( k.size() != 0 )
		{
			ans.emplace_back( k );
			if (k.check())
				NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K_SIMPLE, k );
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
		system.addGearChains( gb.getChainsForCurrentGear(), NS_CORE TGearNumber( i + 1 ), iTarget[i] );
		i++;
	} while ( gb.turnOnNextGear() );

	return solveSimple( system );
}

NS_CORE TK DefKSimple::solveSimple( System& system )
{
	const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();
	const auto elements = { NS_CORE eMainElement::SUN_GEAR, NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE eMainElement::CARRIER, NS_CORE eMainElement::EMPTY };
	const auto countOfEquations = initialData._numberOfGears * initialData._numberOfPlanetaryGears;

	int countOfUncalculatedEquations;

	do
	{
		countOfUncalculatedEquations = 0;
		for ( size_t i = 0; i < initialData._numberOfGears; i++ )
		{
			for ( size_t j = 0; j < initialData._numberOfPlanetaryGears; j++ )
			{

				auto& gearSetVariables = system.getVariablesSet( NS_CORE TGearNumber( i ), j );

				NS_CORE eMainElement undefElem;
				size_t count = 0;

				//считаем количество неизвестных в уравнении
				for ( const auto & elem : elements )
				{
					if ( gearSetVariables[elem].getDefined() == false )
					{
						count++;
						undefElem = elem;
					}
				}

				//если неизвестное одно - можем его найти
				VariableValue value;
				if ( 1 == count )
				{
					value = Equations::calcOne( undefElem, gearSetVariables );
					//отмечаем как известное
					auto& unknowns = system.getUnknownVariables();

					for ( auto& unknown : unknowns )
					{
						if ( unknown.findElementInListeners( NS_CORE TElement( undefElem, j + 1 ), NS_CORE TGearNumber( i + 1 ) ) )
						{
							unknown.setLastValue( value );
						}
					}
				}
				else
				{
					countOfUncalculatedEquations++;
				}
			}
		}
	} while ( countOfUncalculatedEquations != countOfEquations );

	NS_CORE TK ans = getKValuesFromSystem( system );
	return ans;
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
