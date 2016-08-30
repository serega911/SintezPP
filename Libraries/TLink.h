#pragma once

#include <ostream>
#include <istream>
#include <vector>

#include "TElement.h"
#include "GlobalDefines.h"

NS_CORE_START

class TLink;
typedef std::vector<TLink> TLinkArray;

class TLink
{
private:

	TElement									m_elem1;
	TElement									m_elem2;

public:

	TLink(const TElement& elem1, const TElement& elem2);
	TLink();

	const TElement&								getElem1() const;
	const TElement&								getElem2() const;

	void										writeTofile( std::ostream& file ) const;
	bool										loadFromFile( std::istream& file );

	void										print() const;
};

NS_CORE_END
