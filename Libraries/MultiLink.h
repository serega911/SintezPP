#pragma once
#include "../Libraries/Element.h"
#include "../Libraries/Link.h"
#include "../Libraries/IIOItem.h"
#include "GlobalDefines.h"
#include <set>

NS_CORE_START

class MultiLink: public IIOItem
{
private:

	std::set<Element>							m_elements;

public:

	MultiLink( const Element& element );
	MultiLink();

	void										addLinkToChain( const Link & link );
	void										addElementToChain( const Element & elem );
	void										addChainToChain( const MultiLink & chain );

	void										clear();

	bool										find( const Element & element ) const;

	bool										checkElemByOnePlanetarySet() const;
	bool										checkIsChainCorrect() const;
	const Element&								getSomeElement() const;

	size_t										size() const;

	bool										intersect( const MultiLink& chain ) const;

	const std::set<Element>&					getElements() const;

	virtual void								writeToFile( std::ostream& ) const override;
	virtual bool								loadFromFile( std::istream& ) override;

	friend bool operator<( const MultiLink& chain1, const MultiLink& chain2 );
	friend bool operator==( const MultiLink& chain1, const MultiLink& chain2 );
	friend bool operator!=( const MultiLink& chain1, const MultiLink& chain2 );
};

NS_CORE_END
