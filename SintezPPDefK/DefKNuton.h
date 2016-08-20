#pragma once

#include "../Libraries/GlobalDefines.h"

#include "../Libraries/TK.h"
#include "../Libraries/TI.h"

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

	NS_CORE TK									getKValuesFromSystem( const System & system );
	double										calcNorm( const MatrixLine& delta );
	NS_CORE TK									solveNuton( const Jacobi& jacobian, System& system );

	NS_CORE TK									findK( const NS_CORE TCode& code, const NS_CORE TK& initialKValues, const NS_CORE TI& iTarget );

public:

	
	NS_CORE TK									calculate( const NS_CORE TCode& code );
};

NS_ARI_END