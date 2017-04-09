#include "Element.h"
#include "Log.h"

NS_CORE_USING

const Element Element::INPUT =		Element(eMainElement::INPUT, GearSetNumber(0));
const Element Element::OUTPUT =		Element( eMainElement::OUTPUT, GearSetNumber( 0 ) );
const Element Element::BRAKE =		Element( eMainElement::BRAKE, GearSetNumber( 0 ) );
const Element Element::EMPTY =		Element( eMainElement::EMPTY, GearSetNumber( 0 ) );

bool core::Element::isAdditional() const
{
	return isAdditionalElement( m_elemN );
}

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

bool NS_CORE operator<( const Element& elem1, const Element& elem2 )
{
	if ( elem1 == elem2 )
		return false;
	return elem1.getElemN() < elem2.getElemN() ? true :
		elem1.getElemN() == elem2.getElemN() ? elem1.getGearSetN() < elem2.getGearSetN() : false;
}

bool NS_CORE operator==( const Element& elem1, const Element& elem2 )
{
	bool res;
	if ( elem1.getElemN() == eMainElement::BRAKE && elem2.getElemN() == eMainElement::BRAKE && 
		( elem1.getGearSetN() == GearSetNumber( 0 ) || elem2.getGearSetN() == GearSetNumber( 0 ) ) )
			res = true;
	else
		res = elem1.getGearSetN() == elem2.getGearSetN() && elem1.getElemN() == elem2.getElemN();

	return res;
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

void core::Element::print( const eColor& color ) const
{
	Log::log( std::string( 1, convernToSymbol( m_elemN ) ), false, color );
	Log::log( std::to_string( m_gearSetN.getValue() ), false, color );
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

