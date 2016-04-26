#include "../Libraries/TElement.h"
#include "../Libraries/func_lib.h"


const pss::TElement pss::TElement::INPUT = TElement(pss::eMainElement::INPUT, 0);
const pss::TElement pss::TElement::OUTPUT = TElement(pss::eMainElement::OUTPUT, 0);
const pss::TElement pss::TElement::BRAKE = TElement(pss::eMainElement::BRAKE, 0);
const pss::TElement pss::TElement::EMPTY = TElement(pss::eMainElement::EMPTY, 0);
const pss::TElement pss::TElement::PLACEHOLDER = TElement( pss::eMainElement::BUSY , 0 );

pss::TElement::TElement(const pss::eMainElement & elemN, int gearSetN) 
{
	set(elemN, gearSetN);
}

pss::TElement::TElement()
{
}


void pss::TElement::setElemN(const eMainElement & elemN)
{
	m_elemN = elemN;
}

void pss::TElement::setGearSetN(int gearSetN)
{
	m_gearSetN = gearSetN;
}

void pss::TElement::set(const eMainElement & elemN, int gearSetN)
{
	setElemN(elemN);
	setGearSetN(gearSetN);
}

pss::eMainElement pss::TElement::getElemN() const
{
	return m_elemN;
}

int pss::TElement::getGearSetN() const
{
	return m_gearSetN;
}

int pss::TElement::getSerialNumber() const
{
	return (m_gearSetN - 1) * 3 + m_elemN._to_integral() - 1;
}

bool pss::operator<(const TElement& elem1, const TElement& elem2)
{
	//return elem1.getSerialNumber() < elem2.getSerialNumber();
	if ( elem1.m_gearSetN == elem2.m_gearSetN )
	{
		return elem1.m_elemN < elem2.m_elemN;
	}
	else
	{
		return elem1.m_gearSetN < elem2.m_gearSetN;
	}
}

bool pss::operator==(const TElement& elem1, const TElement& elem2)
{
	return ( ( elem1.m_gearSetN == elem2.m_gearSetN ) && ( elem1.m_elemN == elem2.m_elemN ) );
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