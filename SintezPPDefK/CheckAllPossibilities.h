#pragma once

#include <functional>

#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TGearBox.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TCombinatoricsValueArray.h"

class CheckAllPossibilities
{
public:

	static void checkAllInitialKValues( const std::function<bool(const NS_CORE TK&)>& toCall )
	{
		const auto size = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
		NS_CORE TCombinatoricsValueArray combi;
		NS_CORE TK initial( size );
		auto combinator = NS_CORE TSingletons::getInstance()->getCombinatorics();
		size_t combiNum = 0;
		combinator->getOrderedSample( NS_CORE TSingletons::getInstance()->getInitialData()._ranges.size(), size, combiNum++, combi );
		
		do{

			NS_CORE TKValueArray initialK;
			for ( size_t i = 0; i < combi.size(); i++ )
				initialK.push_back( NS_CORE TSingletons::getInstance()->getInitialData()._ranges[combi[i]].getMid() );

			initial.setValues( initialK );

		} while ( toCall( initial ) && combinator->getOrderedSample( NS_CORE TSingletons::getInstance()->getInitialData()._ranges.size(), size, combiNum++, combi ) );

	}

	static void checkAllRatiosPermutations( const std::function<bool(const NS_CORE TI&)>& toCall )
	{
		NS_CORE TI iTarget = NS_CORE TSingletons::getInstance()->getInitialData()._i;
		const auto size = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
		auto combinator = NS_CORE TSingletons::getInstance()->getCombinatorics();
		NS_CORE TIValueArray curI;
		NS_CORE TCombinatoricsValueArray replace;
		size_t combiNum = 0;

		combinator->getPremutation( iTarget.size(), combiNum++, replace );

		do{

			curI.clear();			
			for ( size_t i = 0; i < iTarget.size(); i++ )
				curI.push_back( iTarget[replace[i]] );

		} while ( toCall( NS_CORE TI( curI, NS_CORE TIValue( 0.001 ) ) ) && combinator->getPremutation( iTarget.size(), combiNum++, replace ) );
	}
};