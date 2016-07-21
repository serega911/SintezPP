#pragma once

#include "../Libraries/GlobalDefines.h"

#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"

#include "Jacobi.h"
#include "System.h"
#include "Matrix.h"

NS_PSS_START

class DefKNuton
{
private:

	Jacobi										createJacobian( const System & system );
	Matrix										createMatrix( const Jacobi& jacobian, const System & system );

public:

	TK											findK( const TCode& Code,  const TK& initialKValues );

};

NS_PSS_END