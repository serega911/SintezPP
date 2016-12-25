#include "DefK.h"
#include "../Tests/TestGlue.h"

#include "../Libraries/Log.h"
#include "../Libraries/SettingsItem.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")


int getParamNumber( const std::string& param )
{
	auto ans = 0;
	bool isNegative = false;

	for ( int i = 0; i < param.size(); i++ )
	{
		if ( param[i] == '-' )
			isNegative = true;
		else if ( isdigit( param[i] ) )
			ans = ans * 10 + param[i] - 48;
	}
		

	std::cout << param << " : " << ans << std::endl;

	return ans;
}


int main( int argc, char* argv[] )
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE Log::log( "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====" );

	NS_ARI DefK DK;

	if ( argc == 1 )
	{
		DK.readUIGeneralData();
		DK.readUISpecialData();
	}
	else
	{
		NS_ARI DefK::UISpecialData sData;
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
				sData._ranges.push_back( {std::stof(val), 0} );
			else if ( rangeEndKey == key )
				sData._ranges[sData._ranges.size() - 1].second = std::stof( val );
			else if ( iKey == key )
				sData._i.push_back( std::stof( val ) );
			else
				NS_CORE Log::warning( true, "Wrong argument: " + key, NS_CORE Log::CRITICAL, HERE );
		}

		DK.setUIGeneralData( gData );
		DK.setUISpecialData( sData );
	}

	DK.run();

	return 0;
}