#pragma once

#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"

#include "Determinant.h"
#include "System.h"

namespace pss
{
	class DefKNuton
	{
	private:
		std::vector<std::vector<double>>		m_matrix;									//������� ������� ���������
		pss::TI									m_i;										//������������ ���������

		Determinant								createDeterminant( const System & system );

	public:
		pss::TK									findK( pss::TCode& Code );
		void									run();

	};
}