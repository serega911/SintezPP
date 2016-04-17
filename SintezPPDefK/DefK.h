#pragma once

#include <vector>
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TCode.h"

namespace pss{
	class DefK
	{
	public:
		~DefK(void);		// same
		pss::TK									findK(const pss::TCode& Code, pss::TK K);
		void									run();
	private:
		std::vector<std::vector<double>>		m_matrix;									//������� ������� ���������
		pss::TI									m_iTarget;									//��������� ������������ ���������
		pss::TI									m_iReal;									//����������� ������������ ���������

		bool									podModul(const pss::TCode&, const pss::TK&);
	};

}