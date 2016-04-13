#pragma once
#include <ostream>
#include <istream>

namespace pss
{
	class TElement
	{
	private:
		int											m_elemN;
		int											m_gearSetN;
	public:
		TElement(int elemN, int gearSetN);
		TElement(int serialNumber);
		TElement();
		void										setElemN(int elemN);
		void										setGearSetN(int gearSetN);
		void										set(int elemN, int gearSetN);

		int											getElemN() const;
		int											getGearSetN() const;
		int											getSerialNumber() const;

		static const TElement					INPUT;
		static const TElement					OUTPUT;
		static const TElement					BRAKE;
		static const TElement					EMPTY;

		friend std::ostream&					operator<<(std::ostream& out, const TElement & elem);
		friend std::istream&					operator>>(std::istream& out, const TElement & elem);
	};
	bool										operator<(const TElement& elem1, const TElement& elem2);
	bool										operator==(const TElement& elem1, const TElement& elem2);
	std::ostream&								operator<<(std::ostream& out, const TElement & elem);
	std::istream&								operator>>(std::istream& out, const TElement & elem);
}