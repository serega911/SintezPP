#pragma once
#include <vector>
#include <fstream>

#include "../Libraries/IContainer.h"

namespace pss
{
	class TK: public IContainer
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
		TK(float beginNegative, float endNegative, float beginPositive, float endPositive, float dK);
		const float								operator[](int i) const;
		bool									next();
		void									print() const;
		int										size() const override;
		void									setFinded();
		bool									getFinded();
		void									writeToFile(std::ofstream& file) const override;
		void									loadFromFile(std::ifstream&) override;
	};
}