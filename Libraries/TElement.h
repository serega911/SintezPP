#pragma once
#include <ostream>
#include <istream>
#include "eMainElement.h"

namespace pss
{
	class TElement
	{
	private:
		pss::eMainElement						m_elemN = pss::eMainElement::EMPTY;		//номер элемента
		int										m_gearSetN;		//номер планетарного ряда
	public:
		TElement(const eMainElement & elemN, int gearSetN);
		TElement();

		void										setElemN(const eMainElement & elemN);
		void										setGearSetN(int gearSetN);
		void										set(const eMainElement & elemN, int gearSetN);

		eMainElement								getElemN() const;
		int											getGearSetN() const;
		int											getSerialNumber() const;

		static const TElement					INPUT;		// RK: replace on public static method
		static const TElement					OUTPUT;
		static const TElement					BRAKE;
		static const TElement					EMPTY;

		friend std::ostream&					operator<<(std::ostream& out, const TElement & elem);
	};
	bool										operator<(const TElement& elem1, const TElement& elem2);
	bool										operator==(const TElement& elem1, const TElement& elem2);
	bool										operator!=(const TElement& elem1, const TElement& elem2);
	std::ostream&								operator<<(std::ostream& out, const TElement & elem);

}