#pragma once
#include <ostream>
#include <istream>
#include "eMainElement.h"

namespace pss
{
	class TElement
	{
	private:

		pss::eMainElement						m_elemN;		//номер элемента
		int										m_gearSetN;		//номер планетарного ряда

	public:

		TElement(const eMainElement & elemN, int gearSetN);
		TElement();

		eMainElement							getElemN() const;
		int										getGearSetN() const;
		int										getSerialNumber() const;

		void									print() const;
		void									writeTofile( std::ostream& file ) const;
		bool									loadFromFile( std::istream& file );

		static const TElement					INPUT;		// RK: replace on public static method
		static const TElement					OUTPUT;
		static const TElement					BRAKE;
		static const TElement					EMPTY;


	};

	bool										operator<(const TElement& elem1, const TElement& elem2);
	bool										operator==(const TElement& elem1, const TElement& elem2);
	bool										operator!=(const TElement& elem1, const TElement& elem2);

}