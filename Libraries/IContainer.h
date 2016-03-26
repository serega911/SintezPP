#pragma once

#include <fstream>

namespace pss
{
	class IContainer
	{
	private:

	public:
		virtual int								size() const = 0;
		virtual void							writeToFile(std::ofstream&) const = 0;
		virtual void							loadFromFile(std::ifstream&) = 0;
	};


}