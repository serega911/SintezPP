#include "TestBase.h"

const std::string ari::TestBase::s_pethToResults = "../Results/";

NS_ARI_USING

TestBase::TestBase( const Data& data )
	: m_data( data ) 
{
	const std::string folderName = "w" + std::to_string( getW() ) + "n" + std::to_string( getN() ) + "d" + std::to_string( getD() );
	m_ethalonFolderPath = s_pethToResults + "Ethalon/" + folderName + "/";
	m_workingFolderPath = s_pethToResults + folderName + "/";
};

const std::string& ari::TestBase::getEthalonFolderPath() const
{
	return m_ethalonFolderPath;
}

const std::string& ari::TestBase::getWorkingFolderPath() const
{
	return m_workingFolderPath;
}

size_t ari::TestBase::getD() const
{
	return m_data._d;
}

size_t ari::TestBase::getW() const
{
	return m_data._w;
}

size_t ari::TestBase::getN() const
{
	return m_data._n;
}

