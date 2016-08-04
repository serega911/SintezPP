#include "TElement.h"
#include "TLog.h"

NS_CORE_USING

const TElement TElement::INPUT = TElement(eMainElement::INPUT, 0);
const TElement TElement::OUTPUT = TElement(eMainElement::OUTPUT, 0);
const TElement TElement::BRAKE = TElement(eMainElement::BRAKE, 0);
const TElement TElement::EMPTY = TElement(eMainElement::EMPTY, 0);

TElement::TElement( const eMainElement& elemN, const TGearSetNumber& gearSetN )
	: m_elemN( elemN )
	, m_gearSetN( gearSetN )
{
}

TElement::TElement()
	: TElement( eMainElement::EMPTY, 0 )
{
}

eMainElement TElement::getElemN() const
{
	return m_elemN;
}

TGearSetNumber TElement::getGearSetN() const
{
	return m_gearSetN;
}

int TElement::getSerialNumber() const
{
	return ( m_gearSetN - 1 ) * 3 + convernToInt( m_elemN ) - 1;
}

bool NS_CORE operator<(const TElement& elem1, const TElement& elem2)
{
	return elem1.getGearSetN() < elem2.getGearSetN() ? true :
		elem1.getGearSetN() == elem2.getGearSetN() ? elem1.getElemN() < elem2.getElemN() : false;
}

bool NS_CORE operator==( const TElement& elem1, const TElement& elem2 )
{
	return elem1.getGearSetN() == elem2.getGearSetN() && elem1.getElemN() == elem2.getElemN();
}

bool NS_CORE operator!=( const TElement& elem1, const TElement& elem2 )
{
	return !(elem1 == elem2);
}

void TElement::print() const
{
	TLog::log( std::to_string( convernToSymbol( m_elemN ) ) );
	TLog::log( std::to_string( m_gearSetN ) );
}

void TElement::writeTofile( std::ostream& file ) const
{
	file << convernToSymbol( m_elemN ) << m_gearSetN;
}

bool TElement::loadFromFile( std::istream& file )
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

