#pragma once
#include <vector>
#include <fstream>

#include "../Libraries/IContainer.h"

namespace pss
{
	class TK: public IContainer
	{
	private:

		bool									m_isFinded;
		std::vector<double>						m_K;
		
	public:

		const double							operator[](int i) const;

		void									print() const;
		int										size() const override;
		void									setFinded( const bool finded );
		bool									getFinded() const;
		void									writeToFile(std::ofstream& file) const override;
		void									loadFromFile(std::ifstream&) override;
		void									setValues( const std::vector<double>& values );
		bool									check() const;
	};
}