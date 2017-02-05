#pragma once
#include <vector>
#include "Code.h"
#include "InternalGearRatios.h"
#include "GlobalDefines.h"

NS_CORE_START

class Gaus
{
private:

	std::vector<std::vector<double>>			m_system;
	std::vector<double>							m_solution;

public:

	void										solve();

	void										createSystem( const Code & Code, const InternalGearRatios &k );
	void										createSystemDrivers( const TLinkArray& drivers );

	const std::vector<double>&					getSolution() const;

};

NS_CORE_END