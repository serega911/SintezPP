#pragma once

#include <vector>
namespace pss
{
	class TI
	{
	private:
		std::vector<double>						m_i;
		static double							m_eps;
	public:
		TI();
		TI(const std::vector<double>& i, double eps);
		int										size() const;
		const double							operator[](int i) const;
		bool									operator==(const TI& obj); // RK: const and OUTSIDE class
		void									operator=(const TI& obj);
		void									push_back(double value);
		void									print();
		bool									findIn( double value ) const;

	};
}