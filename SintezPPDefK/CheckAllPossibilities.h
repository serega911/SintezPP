#pragma once

#include <functional>

#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/Ratios.h"
#include "../Libraries/GearBox.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/CombinatoricsValueArray.h"

class CheckAllPossibilities
{
public:

	static void checkAllInitialKValues( const std::function<bool(const NS_CORE InternalGearRatios&)>& toCall )
	{
		const auto size = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
		NS_CORE CombinatoricsValueArray combi;
		NS_CORE InternalGearRatios initial( size );
		auto combinator = NS_CORE Singletons::getInstance()->getCombinatorics();
		size_t combiNum = 0;
		combinator->getOrderedSample( NS_CORE Singletons::getInstance()->getInitialData()._ranges.size(), size, combiNum++, combi );
		
		do{

			NS_CORE InternalGearRatioValueArray initialK;
			for ( size_t i = 0; i < combi.size(); i++ )
				initialK.push_back( NS_CORE Singletons::getInstance()->getInitialData()._ranges[combi[i]].getMid() );

			initial.setValues( initialK );

		} while ( toCall( initial ) && combinator->getOrderedSample( NS_CORE Singletons::getInstance()->getInitialData()._ranges.size(), size, combiNum++, combi ) );

	}

	static void checkAllRatiosPermutations( const std::function<bool(const NS_CORE Ratios&)>& toCall )
	{
		NS_CORE Ratios iTarget = NS_CORE Singletons::getInstance()->getInitialData()._i;
		const auto size = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
		auto combinator = NS_CORE Singletons::getInstance()->getCombinatorics();
		NS_CORE RatioValueArray curI;
		NS_CORE CombinatoricsValueArray replace;
		size_t combiNum = 0;

		combinator->getPremutation( iTarget.size(), combiNum++, replace );

		do{

			curI.clear();			
			for ( size_t i = 0; i < iTarget.size(); i++ )
				curI.push_back( iTarget[replace[i]] );

		} while ( toCall( NS_CORE Ratios( curI, NS_CORE RatioValue( 0.001 ) ) ) && combinator->getPremutation( iTarget.size(), combiNum++, replace ) );
	}
};