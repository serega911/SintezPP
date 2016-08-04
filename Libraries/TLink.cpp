#include "../Libraries/TLink.h"
#include "../Libraries/TLog.h"

NS_CORE_USING

TLink::TLink( const TElement& elem1, const TElement& elem2 )
	: m_elem1( elem1 )
	, m_elem2( elem2 )
{
}

TLink::TLink()
	: TLink( TElement::EMPTY, TElement::EMPTY )
{
}

const TElement& TLink::getElem1() const
{
	return m_elem1;
}

const TElement& TLink::getElem2() const
{
	return m_elem2; 
}

void TLink::writeTofile( std::ostream& file ) const
{
	m_elem1.writeTofile( file );
	m_elem2.writeTofile( file );
}

bool TLink::loadFromFile( std::istream& file )
{
	return m_elem1.loadFromFile( file ) &&	m_elem2.loadFromFile( file );
}

void TLink::print() const
{
	m_elem1.print();
	m_elem2.print();
}


