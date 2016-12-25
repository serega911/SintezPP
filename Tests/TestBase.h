#pragma once

#include "../Libraries/GlobalDefines.h"
#include <string>

NS_ARI_START

struct Data
{
	size_t _w;
	size_t _n;
	size_t _d;
};

class TestBase
{
private:

	static const std::string					s_pethToResults;

	std::string									m_ethalonFolderPath;
	std::string									m_workingFolderPath;
	Data										m_data;

protected:

	TestBase( const Data& data );

	size_t getW() const;
	size_t getN() const;
	size_t getD() const;
	const std::string& getWorkingFolderPath() const;
	const std::string& getEthalonFolderPath() const;

public:

	virtual bool start() = 0;
};

NS_ARI_END