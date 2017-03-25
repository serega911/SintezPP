#pragma once

#include "../Libraries/MappedSystem.h"

NS_ARI_START

// class MappedSystemTest;
// 
// typedef std::shared_ptr<MappedSystemTest> MappedSystemTest_p;

class MappedSystemTest : public NS_CORE MappedSystem
{
	typedef std::map<NS_CORE Element, NS_CORE IMappedSystem::Value> Vector;
	typedef std::vector<Vector> System;

public:
	static NS_CORE MappedSystem_p					createMTest( const NS_CORE ChainArray& chains, const double &mIn0, const NS_CORE InternalGearRatioValue& k );
	static NS_CORE MappedSystem_p					createWTest( const NS_CORE ChainArray& chains, const W &w, const NS_CORE InternalGearRatioValue& k );
	static NS_CORE MappedSystem_p					createMhTest_a_d( const NS_CORE ChainArray& chains, const double &mIn0, const N &n, const W &w, const NS_CORE InternalGearRatioValue& k, const double kpdSum );
};


NS_ARI_END