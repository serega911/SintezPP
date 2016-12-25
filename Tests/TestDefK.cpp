
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TestDefK.h"

NS_ARI_USING

bool ari::TestDefK::start()
{
	NS_ARI Command command = createCommand( { { -5, -2 }, { 2, 5 } }, { 2, 3 } );
		
	system( command.get().c_str() );

	return false;
}

TestDefK* ari::TestDefK::create( const Data& data )
{
	TestDefK* ret = new TestDefK( data );
	return ret;
}

ari::TestDefK::TestDefK( const Data& data )
	: TestBase( data )
{
}

ari::Command ari::TestDefK::createCommand( const std::vector<std::pair<float, float>> & ranges, const std::vector<float> & ratios )
{
	Command command( "SintezPPGenerate.exe" );
	command.addParam( wKey, std::to_string( getW() ) );
	command.addParam( nKey, std::to_string( getN() ) );
	command.addParam( dKey, std::to_string( getD() ) );

	for ( int i = 0; i < ranges.size(); i++ )
	{
		command.addParam( rangeBeginKey, std::to_string( ranges[i].first ) );
		command.addParam( rangeEndKey, std::to_string( ranges[i].second ) );
	}

	for ( int i = 0; i < ratios.size(); i++ )
	{
		command.addParam( iKey, std::to_string( ratios[i] ) );
	}

	return command;
}
