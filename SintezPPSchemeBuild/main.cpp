
#include <iostream>

#include "Scheme.h"
#include "Display.h"
#include "../Libraries/InternalGearRatioValueArray.h"





int main()
{
	NS_ARI Display disp;
	NS_CORE InternalGearRatioValueArray values;

	for ( int i = 0; i < 5; i++ )
		values.push_back( NS_CORE InternalGearRatioValue( i ) );

	NS_ARI Scheme scheme( values );

	scheme.print( disp );

	system( "pause" );
	return 0;
}