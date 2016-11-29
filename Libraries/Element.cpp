#include "Element.h"
#include "Log.h"

NS_CORE_USING

const Element Element::INPUT =		Element(eMainElement::INPUT, GearSetNumber(0));
const Element Element::OUTPUT =		Element( eMainElement::OUTPUT, GearSetNumber( 0 ) );
const Element Element::BRAKE =		Element( eMainElement::BRAKE, GearSetNumber( 0 ) );
const Element Element::EMPTY =		Element( eMainElement::EMPTY, GearSetNumber( 0 ) );

bool core::Element::isCentral() const
{
	return isCentralElement( m_elemN );
}

Element::Element( const eMainElement& elemN, const GearSetNumber& gearSetN )
	: m_elemN( elemN )
	, m_gearSetN( gearSetN )
{
}

Element::Element()
	: Element( eMainElement::EMPTY, GearSetNumber(0) )
{
}

eMainElement Element::getElemN() const
{
	return m_elemN;
}

GearSetNumber Element::getGearSetN() const
{
	return m_gearSetN;
}

int Element::getSerialNumber() const
{
	return ( m_gearSetN.getValue() - 1 ) * 3 + convernToInt( m_elemN ) - 1;
}

bool NS_CORE operator<( const Element& elem1, const Element& elem2 )
{
	return elem1.getGearSetN() < elem2.getGearSetN() ? true :
		elem1.getGearSetN() == elem2.getGearSetN() ? elem1.getElemN() < elem2.getElemN() : false;
}

bool NS_CORE operator==( const Element& elem1, const Element& elem2 )
{
	return elem1.getGearSetN() == elem2.getGearSetN() && elem1.getElemN() == elem2.getElemN();
}

bool NS_CORE operator!=( const Element& elem1, const Element& elem2 )
{
	return !(elem1 == elem2);
}

void Element::print() const
{
	Log::log( std::string( 1, convernToSymbol( m_elemN ) ), false );
	Log::log( std::to_string( m_gearSetN.getValue() ), false );
}

void Element::writeTofile( std::ostream& file ) const
{
	file << convernToSymbol( m_elemN ) << m_gearSetN.getValue();
}

bool Element::loadFromFile( std::istream& file )
{
	char elem, gear;
	file >> elem >> gear;
	if ( !file.eof() )
	{
		m_gearSetN = gear - 48;
		m_elemN = convernToMainElement( elem );
	}
	return !file.eof();
}

