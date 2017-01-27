#include "KinematicSchemeBuilder.h"
#include "../Tests/TestGlue.h"
#include "../Libraries/Log.h"
#include "../Libraries/SettingsItem.h"
#include "../Libraries/Singletons.h"

int main( int argc, char* argv[] )
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE Log::log( "====  Синтез планетарных передач с тремя степенями свободы. Просмотр.  ====\n\n" );

	ari::KinematicSchemeBuilder schemeBuilder;

	if ( argc == 1 )
	{
		schemeBuilder.readUIGeneralData();
		schemeBuilder.readUISpecialData();
	}
	else
	{
// 		const int expectedArgCount = 3;
// 		NS_CORE Log::warning( argc != expectedArgCount + 1, "Wrong Number of arguments", NS_CORE Log::CRITICAL, HERE );
// 		NS_CORE ApplicationBase::UIGeneralData gData;
// 
// 		for ( int i = 1; i < argc; i++ )
// 		{
// 			const NS_CORE SettingsItem item( argv[i] );
// 			const auto& key = item.getKey();
// 			const auto& val = item.getValue();
// 
// 			if ( wKey == key )
// 				gData._w = std::stoi( val );
// 			else if ( nKey == key )
// 				gData._n = std::stoi( val );
// 			else if ( dKey == key )
// 				gData._d = std::stoi( val );
// 			else
// 				NS_CORE Log::warning( true, "Wrong argument: " + key, NS_CORE Log::CRITICAL, HERE );
// 		}
		NS_CORE ApplicationBase::UISpecialData sData;
		NS_CORE ApplicationBase::UIGeneralData gData;

		for ( int i = 1; i < argc; i++ )
		{
			const NS_CORE SettingsItem item( argv[i] );
			const auto& key = item.getKey();
			const auto& val = item.getValue();

			if ( wKey == key )
				gData._w = std::stoi( val );
			else if ( nKey == key )
				gData._n = std::stoi( val );
			else if ( dKey == key )
				gData._d = std::stoi( val );
			else if ( rangeBeginKey == key )
				sData._ranges.push_back( { std::stof( val ), 0 } );
			else if ( rangeEndKey == key )
				sData._ranges[sData._ranges.size() - 1].second = std::stof( val );
			else if ( iKey == key )
				sData._i.push_back( std::stof( val ) );
			else
				NS_CORE Log::warning( true, "Wrong argument: " + key, NS_CORE Log::CRITICAL, HERE );
		}

		schemeBuilder.setUIGeneralData( gData );
		schemeBuilder.setUISpecialData( sData );
		
	}

	if ( !schemeBuilder.checkRequirements() )
		return 1;

	schemeBuilder.run();

	return 0;
}