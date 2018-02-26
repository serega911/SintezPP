#include "DefKSelection.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/MappedSystem.h"
#include "../Libraries/GearBoxWithChanger.h"
#include "../Libraries/Singletons.h"

NS_ARI_USING


NS_CORE InternalGearRatioArray	 DefKSelection::calculate( const NS_CORE Code& Code )
{
	InternalGearRatios K;
	NS_CORE InternalGearRatioArray ans;
	const auto generalData = NS_CORE Singletons::getInstance()->getInitialData();
	const size_t gearsCount = NS_CORE Singletons::getInstance()->getInitialData()._realNumberOfGears;
	NS_CORE GearBoxWithChanger gb( Code );

	do{
		//NS_CORE InternalGearRatioValueArray kValues;
		//kValues.push_back(NS_CORE InternalGearRatioValue(-1.72));
		//kValues.push_back(NS_CORE InternalGearRatioValue(-2.23));
		//InternalGearRatios K(kValues);
		auto ret = podModul( gb, K );

		if (ret.size() >= generalData._realNumberOfGears &&NS_CORE Singletons::getInstance()->getInitialData()._i.isContain(ret))
		{
			//bool isEqual = false;
			//for (const auto& it : ans)
			//	if (it == K)
			//		isEqual = true;

			//if (!isEqual)
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
	const int diff = generalData._numberOfGears - generalData._realNumberOfGears;

	NS_CORE Ratios tmpI( NS_CORE RatioValueArray(), NS_CORE RatioValue( 0.01f ) );	//вектор для полученных передаточных отношений при данном наборе K
	do
	{
		auto system = NS_CORE MappedSystem::createW( gb.getChainsForCurrentGear(), k, inVelocity );
		NS_CORE Gaus::solve( system );
		const auto& solution = system->getSolution();

		if ( solution.size() != 0 )
		{
			const auto calculatedW = solution.at( NS_CORE Element::OUTPUT );
			const auto i = NS_CORE RatioValue(abs(calculatedW) > 0.001 ? inVelocity.getValue() / calculatedW : 0);

			if ( i.getAbs() > 0.001 && core::Singletons::getInstance()->getInitialData()._i.findIn( i ) )
			{
				tmpI.push_back( i );
			}
			else if ((++countOfSkipped) > diff)
			{
				break;
			}
		}
	} while ( gb.turnOnNextGear() );

	return tmpI;
}

size_t ari::DefKSelection::countOfDifferent( const NS_CORE Ratios& calculatedI, const double eps )
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
