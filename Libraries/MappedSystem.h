#pragma once

#include <map>
#include <vector>
#include <memory>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Element.h"
#include "../Libraries/ChainArray.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/IMappedSystem.h"
#include "../Libraries/RatioValue.h"

NS_CORE_START

class MappedSystem;

typedef std::shared_ptr<MappedSystem> MappedSystem_p;

class MappedSystem : public NS_CORE IMappedSystem
{
	typedef std::map<NS_CORE Element, NS_CORE IMappedSystem::Value> Vector;
	typedef std::vector<Vector> System;

protected:

	MappedSystem();
	
	System										m_system;
	Vector										m_solution;

	typedef std::map<NS_CORE Element, double>	M;
	typedef std::map<NS_CORE Element, double>	W;
	typedef std::map<NS_CORE Element, char>		N;

public:

	static MappedSystem_p						createM( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k, const double mIn = 1000 );
	static MappedSystem_p						createW( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k, const NS_CORE RatioValue wIn = NS_CORE RatioValue(100) );

	virtual void								setSolution( const NS_CORE IMappedSystem::Vector& solution ) override;
	virtual NS_CORE IMappedSystem::Matrix		getMatrix() override;

	const MappedSystem::Vector&					getSolution() const;
};


NS_CORE_END