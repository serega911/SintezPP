#pragma once
#include <ostream>
#include <istream>
#include "../Libraries/TElement.h"

namespace pss
{
	class TLink
	{
	private:
		TElement								m_elem1;
		TElement								m_elem2;
	public:
		TLink(const TElement& elem1, const TElement& elem2);
		TLink();

		void									set(const TElement& elem1, const TElement& elem2);

		const TElement&							getElem1() const;
		const TElement&							getElem2() const;

		void									writeTofile( std::ostream& file ) const;
		void									loadFromFile( std::istream& file );

		void									print() const;
	};
}