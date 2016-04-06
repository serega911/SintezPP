#pragma once

#include <vector>
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TCode.h"

namespace pss{
	class DefK
	{
	public:
		DefK() = delete;
		DefK(const pss::TI& I);
		~DefK(void);
		pss::TK									Run(const pss::TCode& Code, pss::TK K);
	private:
		std::vector<std::vector<double>>		m_matrix;									//матрица системы уравнений
		pss::TI									m_iTarget;									//требуемые передаточные отношения
		pss::TI									m_iReal;									//фактические передаточные отношения

		bool									PodModul(const pss::TCode&, const pss::TK&);
	};

}