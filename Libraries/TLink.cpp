#include "../Libraries/TLink.h"

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

std::ostream& pss::operator<<(std::ostream& out, const TLink & link)
{
	out << link.m_elem1 << link.m_elem2;
	return out;
}

std::istream& pss::operator>>(std::istream& in, const TLink & link)
{
	in >> link.m_elem1 >> link.m_elem2;
	return in;
}
