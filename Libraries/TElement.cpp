#include "../Libraries/TElement.h"
#include "../Libraries/func_lib.h"

const pss::TElement pss::TElement::INPUT = TElement(pss::eMainElement::INPUT, 0);
const pss::TElement pss::TElement::OUTPUT = TElement(pss::eMainElement::OUTPUT, 0);
const pss::TElement pss::TElement::BRAKE = TElement(pss::eMainElement::BRAKE, 0);
const pss::TElement pss::TElement::EMPTY = TElement(pss::eMainElement::EMPTY, 0);

pss::TElement::TElement( const pss::eMainElement & elemN, int gearSetN )
	: m_elemN( elemN )
	, m_gearSetN( gearSetN )
{
}

pss::TElement::TElement()
	: TElement( eMainElement::EMPTY, 0 )
{

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
	return (m_gearSetN - 1) * 3 + static_cast<int>(m_elemN) - 1;
}

bool pss::operator<(const TElement& elem1, const TElement& elem2)
{
	return elem1.getGearSetN() < elem2.getGearSetN() ? true :
		elem1.getGearSetN() == elem2.getGearSetN() ? elem1.getElemN() < elem2.getElemN() : false;
}

bool pss::operator==(const TElement& elem1, const TElement& elem2)
{
	return elem1.getGearSetN() == elem2.getGearSetN() && elem1.getElemN() == elem2.getElemN();
}

bool pss::operator!=(const TElement& elem1, const TElement& elem2)
{
	return !(elem1 == elem2);
}

void pss::TElement::print() const
{
	TLog::log( std::to_string( convernToSymbol( m_elemN ) ) );
	TLog::log( std::to_string( m_gearSetN ) );
}

void pss::TElement::writeTofile( std::ostream& file ) const
{
	file << convernToSymbol( m_elemN ) << m_gearSetN;
}

bool pss::TElement::loadFromFile( std::istream& file )
{
	char elem, gear;
	file >> elem >> gear;
	if ( !file.eof() )
	{
		m_gearSetN = gear - 48;
		m_elemN = convernToMainElement( elem );
		//TLog::warning( true, "dont forget for me", TLog::NON_CRITICAL, "TElement::loadFromFile" );
	}
	return !file.eof();
}

