#include "StartAppCommand.h"

NS_ARI_USING

StartAppCommand::StartAppCommand( const std::string appName )
: m_command( appName )
{
}

void StartAppCommand::addParam( const std::string& param, const std::string& value )
{
	m_command += " " + param + "=" + value;
}

int ari::StartAppCommand::execute() const
{
	return system( m_command.c_str() );
}
