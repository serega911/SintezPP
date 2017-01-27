
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TestDefK.h"

NS_ARI_USING

bool ari::TestDefK::start()
{
	SpecialData special;
	special._ranges = { { -5, -2 }, { 2, 5 } };
	special._ratios = { 2, 3 };
	NS_ARI Command command = createCommand( "SintezPPDefK.exe", &special );
		
	system( command.get().c_str() );

	return false;
}

TestDefK* ari::TestDefK::create( const Data& data )
{
	TestDefK* ret = new TestDefK( data );
	return ret;
}

ari::TestDefK::TestDefK( const Data& data )
	: AppManagerBase( data )
{
}

