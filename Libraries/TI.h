#pragma once

#include <vector>
namespace pss
{
	class TI
	{
	private:
		std::vector<float>						m_i;
		static float							m_eps;
	public:
		TI();
		TI(const std::vector<float>& i, float eps);
		int										size() const;
		const float								operator[](int i) const;
		bool									operator==(const TI& obj);
		void									operator=(const TI& obj);
		void									push_back(float value);
		void									print();

	};
}