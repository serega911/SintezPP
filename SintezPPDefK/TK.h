#pragma once
#include <vector>
#include <iostream>

#include "../Libraries/IContainer.h"
#include "../Libraries/TK.h"

namespace pss
{
	class TK: public core::TK
	{
	private:
		bool									m_isFinded;
		double									m_dK;
		std::vector<int>						m_combi;
		std::vector<double>						m_kValues;

	public:
		TK() = delete;
		TK(double dK);

		const double							operator[]( size_t i ) const;
		bool									next();
	};
}