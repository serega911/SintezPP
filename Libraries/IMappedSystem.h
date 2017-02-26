#pragma once

#include <vector>
#include <memory>

#include "GlobalDefines.h"

NS_CORE_START

class IMappedSystem;

typedef std::shared_ptr<IMappedSystem> IMappedSystem_p;

class IMappedSystem
{

public:

	typedef double Value;
	typedef std::vector<Value> Vector;
	typedef std::vector<Vector> Matrix;

	virtual void								setSolution( const Vector& solution ) = 0;
	virtual Matrix								getMatrix() = 0;
};


NS_ARI_END