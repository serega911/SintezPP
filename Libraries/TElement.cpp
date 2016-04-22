#include "../Libraries/TElement.h"
#include "../Libraries/func_lib.h"

const pss::TElement pss::TElement::INPUT = TElement(pss::TMainElement(pss::TMainElement::eMainElements::INPUT), 4);
const pss::TElement pss::TElement::OUTPUT = TElement(pss::TMainElement(pss::TMainElement::eMainElements::OUTPUT), 5);
const pss::TElement pss::TElement::BRAKE = TElement(pss::TMainElement(pss::TMainElement::eMainElements::BRAKE), 6);
const pss::TElement pss::TElement::EMPTY = TElement(pss::TMainElement(pss::TMainElement::eMainElements::EMPTY), 0);
const pss::TElement pss::TElement::PLACEHOLDER = TElement( pss::TMainElement( pss::TMainElement::eMainElements::BUSY ), 9 );

pss::TElement::TElement(TMainElement elemN, int gearSetN)
{
	set(elemN, gearSetN);
}

pss::TElement::TElement()
{
	*this = EMPTY;
}

void pss::TElement::setElemN(const TMainElement & elemN)
{
	m_elemN = elemN;
}

void pss::TElement::setGearSetN(int gearSetN)
{
	m_gearSetN = gearSetN;
}

void pss::TElement::set(const TMainElement & elemN, int gearSetN)
{
	setElemN(elemN);
	setGearSetN(gearSetN);
}

pss::TMainElement pss::TElement::getElemN() const
{
	return m_elemN;
}

int pss::TElement::getGearSetN() const
{
	return m_gearSetN;
}

int pss::TElement::getSerialNumber() const
{
	return (m_gearSetN - 1) * pss::TMainElement::s_numberOfMainElements + static_cast<int>(m_elemN.get()) - 1;
}

bool pss::operator<(const TElement& elem1, const TElement& elem2)
{
	return elem1.getSerialNumber() < elem2.getSerialNumber();
}

bool pss::operator==(const TElement& elem1, const TElement& elem2)
{
	return elem1.getSerialNumber() == elem2.getSerialNumber();
}

bool pss::operator!=(const TElement& elem1, const TElement& elem2)
{
	return !(elem1 == elem2);
}

std::ostream& pss::operator<<(std::ostream& out, const TElement & elem)
{
	out << elem.m_elemN << elem.m_gearSetN;
	return out;
}

// std::istream& pss::operator>>(std::istream& in, TElement & elem)
// {
//	in >> elem.m_elemN;
//	char num;
//	in.get(num);
//	num -= '0';
//	elem.m_gearSetN = int(num);
//	return in;
//}