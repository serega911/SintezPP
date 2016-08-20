#pragma once
#include <vector>
#include "TCode.h"
#include "TK.h"
#include "GlobalDefines.h"

NS_CORE_START

class TGaus
{
private:

	std::vector<std::vector<double>>				m_system;
	std::vector<double>							m_solution;

public:

	void										solve();

	void										createSystem( const TCode & Code, const TK &k );

	void										createSystemDrivers( const std::vector<TLink>& drivers );

	std::vector<std::vector<double>>				getSystem() const;

	const std::vector<double>&					getSolution() const;

};

NS_CORE_END