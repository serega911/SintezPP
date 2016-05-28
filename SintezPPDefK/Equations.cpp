#include "Equations.h"

pss::value pss::Equations::wyllys( variable k, variable w1, variable w2, variable w3 )
{
	return k - ( w3 - w1 ) / ( w3 - w2 );
}

pss::value pss::Equations::empty( variable k, variable w1, variable w2, variable w3 )
{
	return 0;
}

pss::value pss::Equations::dfDk( variable k, variable w1, variable w2, variable w3 )
{
	return 1.0f;
}

pss::value pss::Equations::dfDw1( variable k, variable w1, variable w2, variable w3 )
{
	return 1.0f / ( w2 - w3 );
}

pss::value pss::Equations::dfDw2( variable k, variable w1, variable w2, variable w3 )
{
	return ( w1 - w3 ) / pow( (w3 - w2), 2 );
}

pss::value pss::Equations::dfDw3( variable k, variable w1, variable w2, variable w3 )
{
	return ( w1 - w2 ) / pow( ( w3 - w2 ), 2 );
}

const std::vector<const pss::equation> pss::Equations::s_equations = { dfDk, dfDw1, dfDw2, dfDw3 };