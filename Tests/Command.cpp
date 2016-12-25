#include "Command.h"

NS_ARI_USING

Command::Command( const std::string appName )
	: m_command( appName )
{
}

void Command::addParam( const std::string& param, const std::string& value )
{
	m_command += " " + param + "=" + value;
}

const std::string& ari::Command::get() const
{
	return m_command;
}
