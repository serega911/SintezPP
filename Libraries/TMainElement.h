#pragma once
#include <ostream>
#include <istream>

namespace pss
{
	class TMainElement
	{
	public:
		enum class eMainElements
		{
			SUN_GEAR = 1,
			EPICYCLIC_GEAR = 2,
			CARRIER = 3,
			INPUT = 4,
			OUTPUT = 5,
			BRAKE = 6,
			EMPTY = 0
		};
	private:
		eMainElements							m_mainElement;
	public:
		TMainElement();
		TMainElement(eMainElements mainElement);
		TMainElement(int mainElement);
		eMainElements							get() const;
		void									set(eMainElements mainElement);
		void									operator++();
		bool									end();

		static const int						s_numberOfMainElements;

		friend std::ostream&					operator<<(std::ostream& out, const TMainElement & mainElement);
	};
	std::ostream&								operator<<(std::ostream& out, const TMainElement & mainElement);
}