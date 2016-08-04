#pragma once
#include <vector>
#include "TCode.h"
#include "TK.h"
#include "GlobalDefines.h"

NS_CORE_START

class TGaus
{
private:

	std::vector<std::vector<float>>				m_system;
	std::vector<float>							m_solution;

public:

	void										solve();

	void										createSystem( const TCode & Code, const TK &k );

	void										createSystemDrivers( const std::vector<TLink>& drivers );

	std::vector<std::vector<float>>				getSystem() const;

	const std::vector<float>&					getSolution() const;

};

NS_CORE_END