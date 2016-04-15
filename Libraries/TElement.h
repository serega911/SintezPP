#pragma once
#include <ostream>
#include <istream>
#include "TMainElement.h"

namespace pss
{
	class TElement
	{
	private:
		TMainElement							m_elemN;		//номер элемента
		int										m_gearSetN;		//номер планетарного ряда
	public:
		TElement(TMainElement elemN, int gearSetN);
		//TElement(int serialNumber);
		TElement();

		void										setElemN(const TMainElement & elemN);
		void										setGearSetN(int gearSetN);
		void										set(const TMainElement & elemN, int gearSetN);

		TMainElement								getElemN() const;
		int											getGearSetN() const;
		int											getSerialNumber() const;

		static const TElement					INPUT;
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