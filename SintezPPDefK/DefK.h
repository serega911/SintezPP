#pragma once

#include <vector>
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TCode.h"
#include "../Libraries/GlobalDefines.h"

namespace pss{
	class DefK
	{
	public:
		TK										findK(const TCode& Code, const TK& K);
		void									run();
	private:
		std::vector<std::vector<double>>		m_matrix;									//������� ������� ���������
		TI										m_iTarget;									//��������� ������������ ���������
		TI										m_iReal;									//����������� ������������ ���������

		bool									podModul(const TCode&, const TK&);
	};

}