#include "../Libraries/Log.h"

#include "SolveFunctionDiv.h"

NS_ARI_USING

ari::SolveFunctionDiv_p ari::SolveFunctionDiv::create()
{
	return SolveFunctionDiv_p( new SolveFunctionDiv );
}

float ari::SolveFunctionDiv::calc( const IFunction_p func, const float intervalBeg, const float intervalEnd )
{
	const float eps = 0.00001f;

	float a = intervalBeg;
	float b = intervalEnd;
	float mid;

	do
	{
		mid = ( a + b ) / 2;

		float fa = func->calc( a );
		float fb = func->calc( b );
		float fm = func->calc( mid );

		if ( fa*fm < 0 )
			b = mid;
		else if ( fb * fm < 0 )
			a = mid;
		else if ( fa*fm == 0 )
			return fa == 0 ? a : mid;
		else if ( fb *fm == 0 )
			return fb == 0 ? b : mid;
		else
		{
			NS_CORE Log::warning( true, "Cant solve", NS_CORE Log::NON_CRITICAL, HERE );
			return 0;
		}
	} while ( abs( func->calc( ( a + b ) / 2 ) ) > eps );

	return ( a + b ) / 2;
}
