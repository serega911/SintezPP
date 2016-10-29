#pragma once
#include "../Libraries/Element.h"
#include "../Libraries/Link.h"
#include "GlobalDefines.h"
#include <set>

NS_CORE_START

class Chain
{
private:

	std::set<Element>							m_elements;

public:

	Chain( const Element& element );
	Chain();

	void										addLinkToChain(const Link & link);
	void										addElementToChain(const Element & elem);
	void										addChainToChain(const Chain & chain);

	void										clear();

	bool										find(const Element & element) const;

	bool										checkElemByOnePlanetarySet() const;
	const Element&								getSomeElement() const;

	size_t										size() const;

	bool										intersect(const Chain& chain) const;

	const std::set<Element>&					getElements() const;

	friend bool operator<(const Chain& chain1, const Chain& chain2);
	friend bool operator==( const Chain& chain1, const Chain& chain2 );
	friend bool operator!=( const Chain& chain1, const Chain& chain2 );
};

NS_CORE_END
