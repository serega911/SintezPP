#pragma once
#include <vector>
#include <fstream>

#include "../Libraries/IContainer.h"

namespace pss
{
	class TK: public IContainer
	{
	private:
		enum class eInterval
		{
			BEG_NEGATIVE,
			MID_NEGATIVE,
			BEG_POSITIVE,
			MID_POSITIVE
		};


		float									m_beginNegative;
		float									m_midNegative;
		float									m_endNegative;
		float									m_beginPositive;
		float									m_midPositive;
		float									m_endPositive;
		float									m_dK;
		bool									m_isFinded;
		std::vector<float>						m_K;
		std::vector<eInterval>					m_KInterval;

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