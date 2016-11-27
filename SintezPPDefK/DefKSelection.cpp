#include "DefKSelection.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/GearChanger.h"
#include "../Libraries/Singletons.h"

NS_ARI_USING


NS_CORE InternalGearRatioArray	 DefKSelection::calculate( const NS_CORE Code& Code )
{
	InternalGearRatios K( NS_CORE InternalGearRatioValue( 0.1 ) );
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
	NS_CORE GearChanger gearChanger( code );
	NS_CORE Ratios tmpI( NS_CORE RatioValueArray(), NS_CORE RatioValue( 0.001 ) );	//вектор для полученных передаточных отношений при данном наборе K
	do
	{
		NS_CORE Gaus gaus;
		gaus.createSystem( code, k );
		gaus.createSystemDrivers( gearChanger.getDrivingElementsForGear() );
		gaus.solve();
		if ( gaus.getSolution().size() == 0 )
		{
			continue;
		}

		const auto codeValues = code.getCode();
		double calculatedI = gaus.getSolution()[codeValues[1].getElem1().getSerialNumber()];
		
		if ( abs( calculatedI ) > 0.001 && core::Singletons::getInstance()->getInitialData()._i.findIn( NS_CORE RatioValue( 1.0 / calculatedI ) ) )
		{
			tmpI.push_back( NS_CORE RatioValue( 1.0 / calculatedI ) );
		}

	} while ( gearChanger.next() );

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
