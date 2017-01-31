
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


#include "../Libraries/UISpecialData.h"
#include "TestDefK.h"
#include "StartAppCommandFactory.h"

NS_ARI_USING

bool ari::TestDefK::start()
{
	NS_CORE UISpecialData special;
	special._ranges = { { -5, -2 }, { 2, 5 } };
	special._i = { 2, 3 };
	NS_ARI StartAppCommand_p command = StartAppCommandFactory::create( "SintezPPDefK.exe", getGeneralData() , special );
		
	command->execute();

	return false;
}

TestDefK* ari::TestDefK::create( const NS_CORE UIGeneralData& data )
{
	TestDefK* ret = new TestDefK( data );
	return ret;
}

ari::TestDefK::TestDefK( const NS_CORE UIGeneralData& data )
	: TestBase( data )
{
}

