#pragma once
#include <vector>
#include "Code.h"
#include "InternalGearRatios.h"
#include "IMappedSystem.h"
#include "GlobalDefines.h"

NS_CORE_START

class Gaus
{
private:

	std::vector<std::vector<float>>			m_system;
	std::vector<float>							m_solution;

public:

	void										solve();

	static bool									solve( IMappedSystem_p mappedSystem );

	// 	void										createSystem( const Code & Code, const InternalGearRatios &k );
	// 	void										createSystemDrivers( const TLinkArray& drivers );
	// 
	// 	const std::vector<float>&					getSolution() const;

};

NS_CORE_END