#pragma once

#include "../Libraries/GlobalDefines.h"
#include <string>
#include <vector>

#include "StartAppCommand.h"

#include "../Libraries/UIGeneralData.h"

NS_ARI_START

class TestBase
{
private:

	static const std::string					s_pethToResults;

	std::string									m_ethalonFolderPath;
	std::string									m_workingFolderPath;
	NS_CORE UIGeneralData						m_data;

protected:

	TestBase( const NS_CORE UIGeneralData& data );

	const std::string&							getWorkingFolderPath() const;
	const std::string&							getEthalonFolderPath() const;

	const NS_CORE UIGeneralData&				getGeneralData() const;

public:

	virtual bool								start() = 0;
};

NS_ARI_END