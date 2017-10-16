#pragma once

#include <functional>

#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/Ratios.h"
#include "../Libraries/GearBox.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/OrderedSample.h"
#include "../Libraries/Permutation.h"

class CheckAllPossibilities
{
public:

	static void checkAllInitialKValues( const std::function<bool( const NS_CORE InternalGearRatios& )>& toCall )
	{
		const auto& ranges = NS_CORE Singletons::getInstance()->getInitialData()._ranges;

		NS_CORE InternalGearRatioValueArray values;
		values.reserve( ranges.size() );
		for ( const auto& it : ranges )
			values.push_back(it.getMid());

		NS_CORE OrderedSample<NS_CORE InternalGearRatioValueArray> sample( values, NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears );

		do{
		} while ( toCall( sample.get() ) && sample.next() );
	}

	static void checkAllRatiosPermutations( const std::function<bool( const NS_CORE Ratios& )>& toCall )
	{
		const NS_CORE Ratios iTarget = NS_CORE Singletons::getInstance()->getInitialData()._i;

		NS_CORE Permutation<NS_CORE RatioValueArray> permutation( iTarget.get() );

		do{
		} while ( toCall( NS_CORE Ratios( permutation.get(), NS_CORE RatioValue( 0.001f ) ) ) && permutation.next() );
	}
};