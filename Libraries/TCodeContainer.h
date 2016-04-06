#pragma once
#include <set>
#include <vector>
#include "../Libraries/TCode.h"
#include "../Libraries/IContainer.h"

namespace pss{
	class TCodeContainer: public pss::IContainer
	{
	private:
		std::set<TCode>							m_container;
	public:
		void									add(const TCode& code);
		bool									findIn(const TCode& code) const;

		int										size() const override;
		void									writeToFile(std::ofstream&) const override;
		void									loadFromFile(std::ifstream&) override;
	};
}