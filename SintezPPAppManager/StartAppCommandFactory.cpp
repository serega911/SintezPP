#include "StartAppCommandFactory.h"

NS_ARI_USING

ari::StartAppCommand_p ari::StartAppCommandFactory::create( const std::string& appName )
{
	return StartAppCommand_p( new StartAppCommand( appName ) );
}

ari::StartAppCommand_p ari::StartAppCommandFactory::create( const std::string& appName, const NS_CORE UIGeneralData& generalData )
{
	StartAppCommand_p command = create( appName );

	command->addParam( wKey, std::to_string( generalData._w ) );
	command->addParam( nKey, std::to_string( generalData._n ) );
	command->addParam( dKey, std::to_string( generalData._d ) );

	return command;
}

ari::StartAppCommand_p ari::StartAppCommandFactory::create( const std::string& appName, const NS_CORE UIGeneralData& generalData, const NS_CORE UISpecialData& specialData )
{
	StartAppCommand_p command = create( appName, generalData );

	for ( int i = 0; i < specialData._ranges.size(); i++ )
	{
		command->addParam( rangeBeginKey, std::to_string( specialData._ranges[i].first ) );
		command->addParam( rangeEndKey, std::to_string( specialData._ranges[i].second ) );
	}

	for ( int i = 0; i < specialData._i.size(); i++ )
	{
		if ( specialData._i[i] != 0 )
			command->addParam( iKey, std::to_string( specialData._i[i] ) );
	}

	return command;
}
