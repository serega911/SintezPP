#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"

#include "CalcKinCharacteristics.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

int main( int argc, char* argv[] )
{
	setlocale(LC_CTYPE, "Russian");

	NS_CORE Log::log( "==  —интез планетарных передач с трем€ степен€ми свободы. ќпределение кинематических характеристик.  ==" );

	NS_ARI CalcKinCharacteristics ckc;

	if ( argc == 1 )
	{
		ckc.readUIGeneralData();
		ckc.readUISpecialData();
	}
	else
	{
		NS_CORE UIGeneralData_p gData = NS_CORE UIGeneralData::create();
		NS_CORE UISpecialData_p sData = NS_CORE UISpecialData::create();

		ckc.parseOptions( argc, argv, sData, gData );

		ckc.setUIGeneralData( gData );
		ckc.setUISpecialData( sData );
	}

	if ( !ckc.checkRequirements() )
		return 1;

	ckc.run();

	NS_CORE Singletons::getInstance()->getIOFileManager()->writeSolutionData();

	return 0;

}