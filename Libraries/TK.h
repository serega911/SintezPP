#pragma once
#include <vector>
#include <fstream>

namespace pss
{
	class TK
	{
	private:
		float									m_beginNegative;
		float									m_endNegative;
		float									m_beginPositive;
		float									m_endPositive;
		float									m_dK;
		bool									m_isFinded;
		std::vector<float>						m_K;

	public:
		TK() = delete;
		TK(int countOfPlanetaryGears, float beginNegative, float endNegative, float beginPositive, float endPositive, float dK);
		const float								operator[](int i) const;
		bool									next();
		void									print() const;
		int										size() const;
		void									setFinded();
		bool									getFinded();
		void									writeToFile(std::ofstream& file) const;
	};
}