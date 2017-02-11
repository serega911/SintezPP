#pragma once

#include <map>
#include <vector>
#include <memory>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Element.h"
#include "../Libraries/ChainArray.h"
#include "../Libraries/InternalGearRatios.h"

NS_ARI_START

class MappedSystem;

typedef std::shared_ptr<MappedSystem> MappedSystem_p;

class MappedSystem
{
	typedef double value;
	typedef std::map<NS_CORE Element, value> Vector;
	typedef std::vector<Vector> System;
	typedef std::vector< std::vector<value>> Matrix;

private:

	System										m_system;
	Vector										m_solution;

	MappedSystem( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k );

public:

	static MappedSystem_p						create( const NS_CORE ChainArray& chains, const NS_CORE InternalGearRatios& k );

	void										setSolution( const std::vector<value>& solution);

	Matrix										getMatrix();
};


NS_ARI_END