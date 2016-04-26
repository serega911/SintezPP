#include "../Libraries/TElement.h"
#include "../Libraries/func_lib.h"

const pss::TElement pss::TElement::INPUT = TElement(pss::TMainElement(pss::TMainElement::eMainElements::INPUT), 0);
const pss::TElement pss::TElement::OUTPUT = TElement(pss::TMainElement(pss::TMainElement::eMainElements::OUTPUT), 0);
const pss::TElement pss::TElement::BRAKE = TElement(pss::TMainElement(pss::TMainElement::eMainElements::BRAKE), 0);
const pss::TElement pss::TElement::EMPTY = TElement(pss::TMainElement(pss::TMainElement::eMainElements::EMPTY), 0);
const pss::TElement pss::TElement::PLACEHOLDER = TElement( pss::TMainElement( pss::TMainElement::eMainElements::BUSY ), 0 );

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
	//return elem1.getSerialNumber() < elem2.getSerialNumber();
	if ( elem1.m_gearSetN == elem2.m_gearSetN )
	{
		return elem1.m_elemN.get() < elem2.m_elemN.get();
	}
	else
	{
		return elem1.m_gearSetN < elem2.m_gearSetN;
	}
}

bool pss::operator==(const TElement& elem1, const TElement& elem2)
{
	return ( ( elem1.m_gearSetN == elem2.m_gearSetN ) && ( elem1.m_elemN.get() == elem2.m_elemN.get() ) );
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