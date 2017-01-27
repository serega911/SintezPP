#pragma once

#include "../Libraries/GlobalDefines.h"
#include <string>
#include <vector>

#include "Command.h"

NS_ARI_START

struct Data
{
	size_t _w;
	size_t _n;
	size_t _d;
};

struct SpecialData
{
	std::vector<std::pair<float, float>>		_ranges;
	std::vector<float>							_ratios;
};

class AppManagerBase
{
private:

	static const std::string					s_pethToResults;

	std::string									m_ethalonFolderPath;
	std::string									m_workingFolderPath;
	Data										m_data;

protected:

	AppManagerBase( const Data& data );
	Command										createCommand( const std::string& appName, const SpecialData* special);

	size_t getW() const;
	size_t getN() const;
	size_t getD() const;
	const std::string& getWorkingFolderPath() const;
	const std::string& getEthalonFolderPath() const;

public:

	virtual bool start() = 0;
};

NS_ARI_END