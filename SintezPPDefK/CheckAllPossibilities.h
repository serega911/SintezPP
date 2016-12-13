#pragma once

#include <functional>

#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/Ratios.h"
#include "../Libraries/GearBox.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/CombinatoricsValueArray.h"

class CheckAllPossibilities
{
public:

	static void checkAllInitialKValues( const std::function<bool(const NS_CORE InternalGearRatios&)>& toCall )
	{
		const auto size = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
		const auto& ranges = NS_CORE Singletons::getInstance()->getInitialData()._ranges;
		const bool rangesSize = ranges.size();
		const auto combinator = NS_CORE Singletons::getInstance()->getCombinatorics();
		NS_CORE CombinatoricsValueArray combi;
		NS_CORE InternalGearRatios initial( size );
		
		size_t combiNum = 0;
		combinator->getOrderedSample( rangesSize, size, combiNum++, combi );
		do{
			NS_CORE InternalGearRatioValueArray initialK;
			const  size_t combiSize = combi.size();
			for ( size_t i = 0; i < combiSize; i++ )
				initialK.push_back( ranges[combi[i]].getMid() );

			initial.setValues( initialK );
		} while ( toCall( initial ) && combinator->getOrderedSample( rangesSize, size, combiNum++, combi ) );
	}

	static void checkAllRatiosPermutations( const std::function<bool(const NS_CORE Ratios&)>& toCall )
	{
		const NS_CORE Ratios iTarget = NS_CORE Singletons::getInstance()->getInitialData()._i;
		const auto iTargetSize = iTarget.size();
		const auto combinator = NS_CORE Singletons::getInstance()->getCombinatorics();
		NS_CORE RatioValueArray curI;
		NS_CORE CombinatoricsValueArray replace;
		
		size_t combiNum = 0;
		combinator->getPremutation( iTargetSize, combiNum++, replace );
		do{
			curI.clear();			
			for ( size_t i = 0; i < iTargetSize; i++ )
				curI.push_back( iTarget[replace[i]] );
		} while ( toCall( NS_CORE Ratios( curI, NS_CORE RatioValue( 0.001 ) ) ) && combinator->getPremutation( iTargetSize, combiNum++, replace ) );
	}
};