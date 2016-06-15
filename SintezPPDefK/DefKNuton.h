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

	TI											m_i;										//передаточные отношения

	Jacobi										createJacobian( const System & system );
	Matrix										createMatrix( const Jacobi& jacobian, const System & system );

public:
	TK											findK( TCode& Code );
	void										run();

};

NS_PSS_END