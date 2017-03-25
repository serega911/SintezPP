#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"

#include "TestDefMh.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

int main( int argc, char* argv[] )
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE Log::log( "==  —интез планетарных передач с трем€ степен€ми свободы. ќпределение кинематических характеристик.  ==" );

	NS_ARI TestDefMh ckc;

	if ( !ckc.checkRequirements() )
		return 1;

	ckc.run();

	NS_CORE Singletons::getInstance()->getIOFileManager()->writeSolutionData();

	return 0;

}