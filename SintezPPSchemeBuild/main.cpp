#include "KinematicSchemeBuilder.h"

int main()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE Log::log( "====  Синтез планетарных передач с тремя степенями свободы. Просмотр.  ====\n\n" );

	ari::KinematicSchemeBuilder schemeBuilder;
	schemeBuilder.readUIGeneralData();
	schemeBuilder.run();
	system( "pause" );
}