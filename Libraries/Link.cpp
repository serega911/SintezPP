#include "../Libraries/Link.h"
#include "../Libraries/Log.h"

NS_CORE_USING

Link::Link( const Element& elem1, const Element& elem2 )
	: m_elem1( elem1 )
	, m_elem2( elem2 )
{
}

Link::Link()
	: Link( Element::EMPTY, Element::EMPTY )
{
}

Link::Link( const Link& link )
{
	m_elem1 = link.m_elem1;
	m_elem2 = link.m_elem2;
}

const Element& Link::getElem1() const
{
	return m_elem1;
}

const Element& Link::getElem2() const
{
	return m_elem2; 
}

bool Link::isContain( const Element& elem ) const
{
	return m_elem2 == elem || m_elem1 == elem;
}

void Link::writeTofile( std::ostream& file ) const
{
	m_elem1.writeTofile( file );
	m_elem2.writeTofile( file );
}

bool Link::loadFromFile( std::istream& file )
{
	return m_elem1.loadFromFile( file ) &&	m_elem2.loadFromFile( file );
}

void Link::print() const
{
	m_elem1.print();
	m_elem2.print();
}


core::LinkWithFriction::LinkWithFriction( const Element& elem1, const Element& elem2, int frictionNumber )
	: Link( elem1, elem2 ), m_friction( eMainElement::FRICTION, GearSetNumber( frictionNumber ) )
{

}

core::LinkWithFriction::LinkWithFriction()
	: LinkWithFriction( Element::EMPTY, Element::EMPTY, 0)
{

}

core::LinkWithFriction::LinkWithFriction( const Link& link, int frictionNumber )
	: Link( link ), m_friction( eMainElement::FRICTION, GearSetNumber( frictionNumber ) )
{

}

const Element& core::LinkWithFriction::getFrictionElem() const
{
	return m_friction;
}

bool core::LinkWithFriction::isContain( const Element& elem ) const
{
	return m_friction == elem || Link::isContain( elem );
}

void core::LinkWithFriction::writeTofile( std::ostream& file ) const
{
	Link::writeTofile( file );
	m_friction.writeTofile( file );
}

bool core::LinkWithFriction::loadFromFile( std::istream& file )
{
	return Link::loadFromFile( file ) && m_friction.loadFromFile( file );
}

void core::LinkWithFriction::print() const
{
	Link::print();
	m_friction.print();
}
