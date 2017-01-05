
#include <iostream>

#include "Scheme.h"
#include "Display.h"
#include "PathBuilderLee.h"
#include "SchemeBuilderSwapPrev.h"
#include "../Libraries/InternalGearRatioValueArray.h"
#include "../Libraries/Code.h"





int main()
{
	NS_ARI Display_p disp = NS_ARI Display::create();
	NS_CORE InternalGearRatioValueArray values;

	for ( int i = 0; i < 5; i++ )
		values.push_back( NS_CORE InternalGearRatioValue( i ) );

	NS_CORE Code code;

	NS_ARI IScheme_p scheme = NS_ARI Scheme::create( values );
	NS_ARI IPathBuildStartegy_p pathBuilder = NS_ARI PathBuilderLee::create();
	NS_ARI ISchemeBuildStartegy_p schemeBuilder = NS_ARI SchemeBuilderSwapPrev::create();

	schemeBuilder->run( scheme, pathBuilder, code);



	scheme->print( disp );

	system( "pause" );
	return 0;
}