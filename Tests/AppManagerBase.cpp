#include "AppManagerBase.h"

const std::string ari::AppManagerBase::s_pethToResults = "../Results/";

NS_ARI_USING

AppManagerBase::AppManagerBase( const Data& data )
	: m_data( data ) 
{
	const std::string folderName = "w" + std::to_string( getW() ) + "n" + std::to_string( getN() ) + "d" + std::to_string( getD() );
	m_ethalonFolderPath = s_pethToResults + "Ethalon/" + folderName + "/";
	m_workingFolderPath = s_pethToResults + folderName + "/";
};

ari::Command ari::AppManagerBase::createCommand( const std::string& appName, const SpecialData* special )
{
	Command command( appName );
	command.addParam( wKey, std::to_string( getW() ) );
	command.addParam( nKey, std::to_string( getN() ) );
	command.addParam( dKey, std::to_string( getD() ) );

	if ( nullptr != special )
	{
		for ( int i = 0; i < special->_ranges.size(); i++ )
		{
			command.addParam( rangeBeginKey, std::to_string( special->_ranges[i].first ) );
			command.addParam( rangeEndKey, std::to_string( special->_ranges[i].second ) );
		}

		for ( int i = 0; i < special->_ratios.size(); i++ )
		{
			command.addParam( iKey, std::to_string( special->_ratios[i] ) );
		}
	}

	return command;
}

const std::string& ari::AppManagerBase::getEthalonFolderPath() const
{
	return m_ethalonFolderPath;
}

const std::string& ari::AppManagerBase::getWorkingFolderPath() const
{
	return m_workingFolderPath;
}

size_t ari::AppManagerBase::getD() const
{
	return m_data._d;
}

size_t ari::AppManagerBase::getW() const
{
	return m_data._w;
}

size_t ari::AppManagerBase::getN() const
{
	return m_data._n;
}

