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
		std::vector<std::vector<double>>		m_matrix;									//матрица системы уравнений
		TI										m_iTarget;									//требуемые передаточные отношения
		TI										m_iReal;									//фактические передаточные отношения

		bool									podModul(const TCode&, const TK&);
	};

}