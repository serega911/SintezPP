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
		const int expectedArgCount = 3;
		NS_CORE Log::warning( argc != expectedArgCount + 1, "Wrong Number of arguments", NS_CORE Log::CRITICAL, HERE );
		NS_CORE UIGeneralData gData;

		for ( int i = 1; i < argc; i++ )
		{
			const NS_CORE SettingsItem item( argv[i] );
			const auto& key = item.getKey();
			const auto& val = item.getValue();

			if ( wKey == key )
				gData._w = std::stoi(val);
			else if ( nKey == key )
				gData._n = std::stoi( val );
			else if ( dKey == key )
				gData._d = std::stoi( val );
			else
				NS_CORE Log::warning( true, "Wrong argument: " + key, NS_CORE Log::CRITICAL, HERE );
		}

		generator.setUIGeneralData( gData );
	}

	if ( !generator.checkRequirements() )
		return 1;
	
	generator.run();

	NS_CORE Singletons::getInstance()->getIOFileManager()->writeSolutionData();

	return 0;
}

