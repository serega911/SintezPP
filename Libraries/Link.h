#pragma once

#include <ostream>
#include <istream>
#include <vector>

#include "Element.h"
#include "GlobalDefines.h"

NS_CORE_START

class Link;
class LinkWithFriction;

typedef std::vector<Link> TLinkArray;
typedef std::vector<LinkWithFriction> TLinkWithFrictionArray;

class Link
{
private:

	Element										m_elem1;
	Element										m_elem2;

public:

	Link(const Element& elem1, const Element& elem2);
	Link( const Link& link );
	Link();

	const Element&								getElem1() const;
	const Element&								getElem2() const;

	virtual bool								isContain( const Element& elem ) const;

	virtual void								writeTofile( std::ostream& file ) const;
	virtual bool								loadFromFile( std::istream& file );

	virtual void								print() const;
};

class LinkWithFriction : public Link
{
private:

	Element										m_friction;

public:

	LinkWithFriction( const Element& elem1, const Element& elem2, int frictionNumber );
	LinkWithFriction( const Link& link, int frictionNumber );
	LinkWithFriction();

	const Element&								getFrictionElem() const;

	virtual bool								isContain( const Element& elem ) const override;

	virtual void								writeTofile( std::ostream& file ) const override;
	virtual bool								loadFromFile( std::istream& file ) override;

	virtual void								print() const;

};

NS_CORE_END
