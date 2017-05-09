#include "DefKSelection.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/MappedSystem.h"
#include "../Libraries/GearBoxWithChanger.h"
#include "../Libraries/Singletons.h"

NS_ARI_USING


NS_CORE InternalGearRatioArray	 DefKSelection::calculate( const NS_CORE Code& Code )
{
	InternalGearRatios K( NS_CORE InternalGearRatioValue( 0.1f ) );
	NS_CORE InternalGearRatioArray	 ans;
	bool isSolutionExist = false;
	size_t failedCount = 0;
	const size_t failedLimit = 5;
	size_t calculated = 0;

	const size_t gearsCount = NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears;

	do{
		auto ret = podModul( Code, K );
		if ( NS_CORE Singletons::getInstance()->getInitialData()._i == ret )
		{
			ans.emplace_back( K );
		}
		else if ( gearsCount > countOfDifferent( ret ) )
		{
			if ( failedCount < failedLimit )
				failedCount++;
			else
				break;
		}

	} while ( K.next() );

	return ans;
}

NS_CORE Ratios DefKSelection::podModul( const NS_CORE Code & code, const InternalGearRatios &k )
{
	NS_CORE GearBoxWithChanger gb( code );
	gb.createChains();

	NS_CORE Ratios tmpI( NS_CORE RatioValueArray(), NS_CORE RatioValue( 0.001f ) );	//вектор для полученных передаточных отношений при данном наборе K
	do
	{
		auto system = NS_CORE MappedSystem::createW( gb.getChainsForCurrentGear(), k );
		NS_CORE Gaus::solve( system );
		const auto& solution = system->getSolution();

		if ( solution.size() != 0 )
		{
			const auto calculatedW = solution.at( NS_CORE Element::OUTPUT );

			if ( abs( calculatedW ) > 0.001f && core::Singletons::getInstance()->getInitialData()._i.findIn( NS_CORE RatioValue( 1.0f / calculatedW ) ) )
			{
				tmpI.push_back( NS_CORE RatioValue( 1.0f / calculatedW ) );
			}
		}



	} while ( gb.turnOnNextGear() );

	return tmpI;
}

size_t ari::DefKSelection::countOfDifferent( const NS_CORE Ratios& calculatedI )
{
	size_t ret = 0;
	bool isUnique = true;
	const int size = calculatedI.size();

	for ( int i = 0; i < size; i++ )
	{
		if ( calculatedI[i] != NS_CORE RatioValue( 0 ) )
		{
			isUnique = true;
			const int calcISize = calculatedI.size();
			for ( int j = i + 1; j < calcISize; j++ )
			{
				if ( calculatedI[i] == calculatedI[j] )
				{
					isUnique = false;
					break;
				}
			}
			if ( isUnique )
			{
				ret++;
			}
		}
	}

	return ret;
}
