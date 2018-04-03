#include "DefK.h"

#include "../Libraries/TestGlue.h"
#include "../Libraries/Log.h"
#include "../Libraries/SettingsItem.h"
#include "../Libraries/Singletons.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

int main( int argc, char* argv[] )
{
	setlocale(LC_CTYPE, "Russian");
	NS_CORE Log::log( "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====" );

	NS_ARI DefK DK;

	if ( argc == 1 )
	{
		DK.readUIGeneralData();
		DK.readUISpecialData();
	}
	else
	{
		NS_CORE UISpecialData_p sData = NS_CORE UISpecialData::create();
		NS_CORE UIGeneralData_p gData = NS_CORE UIGeneralData::create();

		DK.parseOptions( argc, argv, sData, gData );

		DK.setUIGeneralData( gData );
		DK.setUISpecialData( sData );
	}

	if ( !DK.checkRequirements() )
		return 1;

	NS_CORE Singletons::getInstance()->getIOFileManager()->writeSolutionData();

	DK.run();

	return 0;
}