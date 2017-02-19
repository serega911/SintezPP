#pragma once

#include <ostream>
#include <istream>
#include <vector>

#include "Element.h"
#include "GlobalDefines.h"

NS_CORE_START

class Link;
typedef std::vector<Link> TLinkArray;

class Link
{
private:

	Element										m_elem1;
	Element										m_elem2;

public:

	Link(const Element& elem1, const Element& elem2);
	Link();

	const Element&								getElem1() const;
	const Element&								getElem2() const;

	bool										isContain( const Element& elem ) const;

	void										writeTofile( std::ostream& file ) const;
	bool										loadFromFile( std::istream& file );

	void										print() const;
};

NS_CORE_END
