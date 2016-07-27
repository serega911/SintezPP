#include "../Libraries/TLink.h"
#include "../Libraries/TLog.h"

pss::TLink::TLink(const pss::TElement& elem1, const pss::TElement& elem2)
{
	set(elem1, elem2);
}

pss::TLink::TLink()
{
	set(pss::TElement::EMPTY, pss::TElement::EMPTY);
}

void pss::TLink::set(const pss::TElement& elem1, const pss::TElement& elem2)
{
	m_elem1 = elem1;
	m_elem2 = elem2;
}

const pss::TElement& pss::TLink::getElem1() const
{
	return m_elem1;
}

const pss::TElement& pss::TLink::getElem2() const
{
		return m_elem2; 
}

void pss::TLink::writeTofile( std::ostream& file ) const
{
	m_elem1.writeTofile( file );
	m_elem2.writeTofile( file );
	file << ' ';
}

void pss::TLink::loadFromFile( std::istream& file )
{
	m_elem1.loadFromFile( file );
	m_elem2.loadFromFile( file );
}

void pss::TLink::print() const
{
	m_elem1.print();
	m_elem2.print();
}


