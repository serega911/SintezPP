#include "../Libraries/TElement.h"
#include "../Libraries/func_lib.h"

const pss::TElement pss::TElement::INPUT = TElement(4,4);
const pss::TElement pss::TElement::OUTPUT = TElement(5, 5);
const pss::TElement pss::TElement::BRAKE = TElement(6, 6);
const pss::TElement pss::TElement::EMPTY = TElement(0, 0);

pss::TElement::TElement(int elemN, int gearSetN)
{
	set(elemN, gearSetN);
}

pss::TElement::TElement()
{
	*this = EMPTY;
}

pss::TElement::TElement(int serialNumber)
{
	set(serialNumber % 3 + 1, serialNumber / 3 + 1);
}

void pss::TElement::setElemN(int elemN)
{
	m_elemN = elemN;
}

void pss::TElement::setGearSetN(int gearSetN)
{
	m_gearSetN = gearSetN;
}

void pss::TElement::set(int elemN, int gearSetN)
{
	setElemN(elemN);
	setGearSetN(gearSetN);
}

int pss::TElement::getElemN() const
{
	return m_elemN;
}

int pss::TElement::getGearSetN() const
{
	return m_gearSetN;
}

int pss::TElement::getSerialNumber() const
{
	return (m_gearSetN - 1) * 3 + m_elemN - 1;
}

bool pss::operator<(const TElement& elem1, const TElement& elem2)
{
	return elem1.getSerialNumber() < elem2.getSerialNumber();
}

bool pss::operator==(const TElement& elem1, const TElement& elem2)
{
	return elem1.getSerialNumber() == elem2.getSerialNumber();
}

std::ostream& pss::operator<<(std::ostream& out, const TElement & elem)
{
	out << elem.m_elemN << elem.m_gearSetN;
	return out;
}

std::istream& pss::operator>>(std::istream& in, const TElement & elem)
{
	in >> elem.m_elemN >> elem.m_gearSetN;
	return in;
}
