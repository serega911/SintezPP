#pragma once

#include "../Libraries/GlobalDefines.h"

#include "../Libraries/InternalGearRatioArray.h"
#include "../Libraries/Ratios.h"

#include "Jacobi.h"
#include "System.h"
#include "Matrix.h"

NS_ARI_START

class DefKNuton
{
private:

	Jacobi										createJacobian( const System & system );
	Matrix										createMatrix( const Jacobi& jacobian, const System & system );
	MatrixLine									createRightParts( const System & system );

	NS_CORE InternalGearRatios					geInternalGearRatioValuesFromSystem( const System & system );
	float										calcNorm( const MatrixLine& delta );
	NS_CORE InternalGearRatios					solveNuton( const Jacobi& jacobian, System& system );

	NS_CORE InternalGearRatios					findK( const NS_CORE Code& code, const NS_CORE InternalGearRatios& initialKValues, const NS_CORE Ratios& iTarget );

public:


	NS_CORE InternalGearRatioArray				calculate( const NS_CORE Code& code );
};

NS_ARI_END