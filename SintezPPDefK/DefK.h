#pragma once

#include <vector>
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TCode.h"

namespace pss{
	class DefK
	{
	public:
		DefK();				// RK: dont need if not used or use "= default" to explicit say that it empty
		~DefK(void);		// same
		pss::TK									findK(const pss::TCode& Code, pss::TK K);
		void									run();
	private:
		std::vector<std::vector<double>>		m_matrix;									//матрица системы уравнений
		pss::TI									m_iTarget;									//требуемые передаточные отношения
		pss::TI									m_iReal;									//фактические передаточные отношения

		bool									podModul(const pss::TCode&, const pss::TK&);	// RK: const
	};

}