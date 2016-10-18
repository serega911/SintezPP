#include "DefKSelection.h"
#include "../Libraries/TGaus.h"
#include "../Libraries/TGearChanger.h"
#include "../Libraries/TSingletons.h"

NS_ARI_USING

NS_CORE TKArray	 DefKSelection::calculate( const NS_CORE TCode& Code )
{
	TK K( NS_CORE TKValue( 0.1 ) );
	NS_CORE TKArray	 ans;
	bool isSolutionExist = false;
	size_t failedCount = 0;
	const size_t failedLimit = 5;
	size_t calculated = 0;

	do{
		auto ret = podModul( Code, K );
		if ( core::TSingletons::getInstance()->getInitialData()._i == ret )
		{
			ans.emplace_back( K );
		}
		else if ( core::TSingletons::getInstance()->getInitialData()._numberOfGears > countOfDifferent( core::TSingletons::getInstance()->getInitialData()._i ) )
		{
			if ( failedCount < failedLimit )
				failedCount++;
			else
				break;
		}
		
	} while ( K.next() );

	return ans;
}

NS_CORE TI DefKSelection::podModul( const NS_CORE TCode & code, const TK &k )
{
	NS_CORE TGearChanger gearChanger( code );
	NS_CORE TI tmpI( NS_CORE TIValueArray(), NS_CORE TIValue( 0.001 ) );	//вектор для полученных передаточных отношений при данном наборе K
	do
	{
		NS_CORE TGaus gaus;
		gaus.createSystem( code, k );
		gaus.createSystemDrivers( gearChanger.getDrivingElementsForGear() );
		gaus.solve();
		if ( gaus.getSolution().size() == 0 )
		{
			return NS_CORE TI();
		}
		const auto codeValues = code.getCode();
		double calculatedI = gaus.getSolution()[codeValues[1].getElem1().getSerialNumber()];
		if ( abs( calculatedI ) > 0.001 && core::TSingletons::getInstance()->getInitialData()._i.findIn( NS_CORE TIValue( 1.0 / calculatedI ) ) )
		{
			tmpI.push_back( NS_CORE TIValue( 1.0 / calculatedI ) );
		}
		else
		{
			return NS_CORE TI();
		}

	} while ( gearChanger.next() );

	return tmpI;
}

size_t ari::DefKSelection::countOfDifferent( const NS_CORE TI& calculatedI )
{
	size_t ret = 0;
	bool isUnique = true;
	for ( int i = 0; i < calculatedI.size() - 1; i++ )
	{
		isUnique = true;
		for ( int j = i + 1; j < calculatedI.size(); j++ )
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

	return ++ret;
}
