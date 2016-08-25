#pragma once

#include <functional>
#include <algorithm>

#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TGearBox.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/GlobalDefines.h"

class CheckAllPossibilities
{
public:

	static void checkAllInitialKValues( const std::function<bool(const NS_CORE TK&)>& toCall )
	{
		const auto size = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

		std::vector<int> combi;
		for ( size_t i = 0; i < size; i++ )
			combi.push_back( 0 );

		NS_CORE TK initial( size );

		do{

			NS_CORE TKValueArray initialK;
			for ( size_t i = 0; i < combi.size(); i++ )
				initialK.push_back( NS_CORE TSingletons::getInstance()->getInitialData()._ranges[combi[i]].getMid() );

			initial.setValues( initialK );

		} while ( toCall( initial ) && NS_CORE next_combination_repetition( combi, NS_CORE TSingletons::getInstance()->getInitialData()._ranges.size() - 1, 0 ) );

	}

	static void checkAllRatiosPermutations( const std::function<bool(const NS_CORE TI&)>& toCall )
	{
		NS_CORE TI iTarget = NS_CORE TSingletons::getInstance()->getInitialData()._i;
		const auto size = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

		std::vector<int> replace;
		for ( size_t i = 0; i < iTarget.size(); i++ )
			replace.push_back( i );

		NS_CORE TIValueArray curI;

		NS_CORE TK k( size );

		do{

			curI.clear();			
			for ( size_t i = 0; i < iTarget.size(); i++ )
				curI.push_back( iTarget[replace[i]] );

		} while ( toCall( NS_CORE TI( curI,NS_CORE TIValue( 0.001 ) ) ) && std::next_permutation( replace.begin(), replace.end() ) );
	}
};