#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"


NS_ARI_START

class TestDefMh
	: public NS_CORE ApplicationBase
{
private:

	typedef std::pair<NS_CORE Element, double>	Minit;
	typedef std::map<NS_CORE Element, double>	M;
	typedef std::map<NS_CORE Element, double>	W;
	typedef std::map<NS_CORE Element, char>	N;
	
	N											calcN( const W& w, const M& m );

public:

	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END