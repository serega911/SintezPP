#pragma once
#include <vector>
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"

namespace pss
{
	class TGaus
	{
	private:
		std::vector<std::vector<float>>			m_system;
		std::vector<float>						m_solution;
	public:
		void									solve();
		void									createSystem(const pss::TCode & Code, const pss::TK &k);
		void									createSystemDrivers(const std::vector<pss::TLink>& drivers);
		const std::vector<float>&				getSolution();
	};
}