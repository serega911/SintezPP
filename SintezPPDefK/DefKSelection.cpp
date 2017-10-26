#include "DefKSelection.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/MappedSystem.h"
#include "../Libraries/GearBoxWithChanger.h"
#include "../Libraries/Singletons.h"

NS_ARI_USING


NS_CORE InternalGearRatioArray	 DefKSelection::calculate( const NS_CORE Code& Code )
{
	InternalGearRatios K( NS_CORE InternalGearRatioValue( 0.1f ) );
	NS_CORE InternalGearRatioArray ans;
	const size_t gearsCount = NS_CORE Singletons::getInstance()->getInitialData()._realNumberOfGears;
	NS_CORE GearBoxWithChanger gb( Code );

	do{
		auto ret = podModul( gb, K );

		if ( NS_CORE Singletons::getInstance()->getInitialData()._i.isContain( ret ) )
		{
			ans.emplace_back( K );
		}

	} while ( K.next() );

	return ans;
}

NS_CORE Ratios DefKSelection::podModul( NS_CORE GearBoxWithChanger & gb, const InternalGearRatios &k )
{
	const NS_CORE RatioValue inVelocity = NS_CORE RatioValue( 100 );
	gb.reset();

	const auto generalData = NS_CORE Singletons::getInstance()->getInitialData();
	int countOfSkipped = 0;
	const int diff = generalData._realNumberOfGears - generalData._realNumberOfGears;

	NS_CORE Ratios tmpI( NS_CORE RatioValueArray(), NS_CORE RatioValue( 0.01f ) );	//вектор для полученных передаточных отношений при данном наборе K
	do
	{
		auto system = NS_CORE MappedSystem::createW( gb.getChainsForCurrentGear(), k, inVelocity );
		NS_CORE Gaus::solve( system );
		const auto& solution = system->getSolution();

		if ( solution.size() != 0 )
		{
			const auto calculatedW = solution.at( NS_CORE Element::OUTPUT );

			if ( abs( calculatedW ) > 0.001f && core::Singletons::getInstance()->getInitialData()._i.findIn( NS_CORE RatioValue( inVelocity.getValue() / calculatedW ) ) )
			{
				tmpI.push_back( NS_CORE RatioValue( inVelocity.getValue() / calculatedW ) );
			}
			else if ((++countOfSkipped) > diff)
			{
				break;
			}
		}
	} while ( gb.turnOnNextGear() );

	return tmpI;
}

size_t ari::DefKSelection::countOfDifferent( const NS_CORE Ratios& calculatedI, const float eps )
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
				if ( abs (calculatedI[i].getValue() - calculatedI[j].getValue() ) < eps )
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
