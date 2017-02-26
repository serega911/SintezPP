#include "Generate.h"

#include "../Libraries/TestGlue.h"
#include "../Libraries/SettingsItem.h"
#include "../Libraries/Singletons.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

NS_ARI_USING

int main(int argc, char* argv[])
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE Log::log( "====  Синтез планетарных передач с тремя степенями свободы. Генерация.  ====\n\n" );

	Generate generator;

	if ( argc == 1 )
	{
		generator.readUIGeneralData();
	}
	else 
	{
		NS_CORE UIGeneralData_p gData = NS_CORE UIGeneralData::create();

		generator.parseOptions( argc, argv, nullptr, gData );

		generator.setUIGeneralData( gData );
	}

	if ( !generator.checkRequirements() )
		return 1;
	
	generator.run();

	NS_CORE Singletons::getInstance()->getIOFileManager()->writeSolutionData();

	return 0;
}

