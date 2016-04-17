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
			INPUT = 4,							// RK: why diff logic types in one enum
			OUTPUT = 5,
			BRAKE = 6,
			EMPTY = 0
		};
	private:
		eMainElements							m_mainElement;
	public:
		TMainElement();
		explicit TMainElement(eMainElements mainElement);		// RK: Expected to be explicit
		TMainElement(int mainElement);					// RK: same

		eMainElements							get() const;
		void									set(const eMainElements & mainElement);
		void									operator++();		// RK: use BETTER_ENUM
		bool									end();	// RK: strange name

		static const int						s_numberOfMainElements;		// RK: Dont be PUBLIC

		friend std::ostream&					operator<<(std::ostream& out, const TMainElement & mainElement);
	};
}