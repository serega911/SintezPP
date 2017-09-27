#include "KinematicSchemeBuilder.h"
#include "../Libraries/TestGlue.h"
#include "../Libraries/Log.h"
#include "../Libraries/SettingsItem.h"
#include "../Libraries/Singletons.h"

int main( int argc, char* argv[] )
{
	setlocale(LC_CTYPE, "Russian");

	NS_CORE Log::log( "====  Синтез планетарных передач с тремя степенями свободы. Просмотр.  ====\n\n" );

	ari::KinematicSchemeBuilder schemeBuilder;

	if ( argc == 1 )
	{
		schemeBuilder.readUIGeneralData();
		schemeBuilder.readUISpecialData();
	}
	else
	{
		NS_CORE UISpecialData_p sData = NS_CORE UISpecialData::create();
		NS_CORE UIGeneralData_p gData = NS_CORE UIGeneralData::create();

		schemeBuilder.parseOptions( argc, argv, sData, gData );

		schemeBuilder.setUIGeneralData( gData );
		schemeBuilder.setUISpecialData( sData );
	}

	if ( !schemeBuilder.checkRequirements() )
		return 1;

	schemeBuilder.run();

	return 0;
}