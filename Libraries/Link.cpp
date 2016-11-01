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

const Element& Link::getElem1() const
{
	return m_elem1;
}

const Element& Link::getElem2() const
{
	return m_elem2; 
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


