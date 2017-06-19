#include "TestBase.h"

const std::string ari::TestBase::s_pethToResults = "../Results/";

NS_ARI_USING

TestBase::TestBase( const NS_CORE UIGeneralData& data )
: m_data( data )
{
	const std::string folderName = "w" + std::to_string( m_data._w ) + "n" + std::to_string( m_data._n ) + "d" + std::to_string( m_data._d );
	m_ethalonFolderPath = s_pethToResults + "Ethalon/" + folderName + "/";
	m_workingFolderPath = s_pethToResults + folderName + "/";
};

const NS_CORE UIGeneralData& ari::TestBase::getGeneralData() const
{
	return m_data;
}

const std::string& ari::TestBase::getEthalonFolderPath() const
{
	return m_ethalonFolderPath;
}

const std::string& ari::TestBase::getWorkingFolderPath() const
{
	return m_workingFolderPath;
}

