#pragma once

#include "../Libraries/GlobalDefines.h"

#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"

#include "Determinant.h"
#include "System.h"

NS_PSS_START

class DefKNuton
{
private:
	std::vector<std::vector<double>>			m_matrix;									//матрица системы уравнений
	TI											m_i;										//передаточные отношения

	Determinant									createDeterminant( const System & system );

public:
	TK											findK( TCode& Code );
	void										run();

};

NS_PSS_END