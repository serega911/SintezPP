#include "Scheme.h"
#include "GearSetFactory.h"
#include "Display.h"

#include "../Libraries/Singletons.h"

NS_ARI_USING

const int Scheme::s_setWidth = 9;
const int Scheme::s_height = 13;



void ari::Scheme::printElement( NS_ARI ISchemeElement_p set, const IDisplay_p& disp ) const
{
	const auto& cords = set->getCordsWorldSpace();

	for ( const auto& it : cords )
	{
		char c;

		if ( it->isConsist( NS_CORE Element::INPUT ) )
			c = 'I';
		else if ( it->isConsist( NS_CORE Element::OUTPUT ) )
			c = 'O';
		else if ( it->isConsist( NS_CORE Element::BRAKE ) )
			c = 'B';
		else
			c = '#';

		disp->print( it->getCord(), c );
	}

}

Scheme::Scheme( const NS_CORE InternalGearRatios k )
{
	const int count = k.size();

	m_width = count * s_setWidth;
	const ari::Cordinate delta( s_setWidth, 0 );
	ari::Cordinate pos( s_setWidth / 2, - s_height / 2 );

	for ( int i = 0; i < count; i++ )
	{
		m_staticElements.emplace_back( GearSetFactory::createGearSet( k[i], NS_CORE GearSetNumber( i + 1 ), pos ) );
		pos = pos + delta;
	}

	Link_p brake = Link::create();
	brake->addElem( NS_CORE Element::BRAKE );
	for ( int i = 0; i < m_width; i++ )
	{	
		brake->addCord( Cordinate( i, 0 ) );
	}
	m_staticElements.emplace_back( brake );

	Link_p input = Link::create();
	input->addElem( NS_CORE Element::INPUT );
	input->addCord( Cordinate( 0, -s_height + 1 ) );
	m_staticElements.emplace_back( input );

	Link_p output = Link::create();
	output->addElem( NS_CORE Element::OUTPUT );
	output->addCord( Cordinate( m_width - 1, -s_height + 1 ) );
	m_staticElements.emplace_back( output );
}

std::vector<ISchemeElement_p> ari::Scheme::getAllElements() const
{
	std::vector<ISchemeElement_p> ret;
	ret.reserve( m_staticElements.size() + m_links.size() ); // preallocate memory
	ret.insert( ret.end(), m_staticElements.begin(), m_staticElements.end() );
	ret.insert( ret.end(), m_links.begin(), m_links.end() );

	return ret;
}

ari::Scheme_p ari::Scheme::create( const NS_CORE InternalGearRatios k )
{
	return Scheme_p( new Scheme( k ) );
}

void ari::Scheme::addElementsToLink( Link_p & link, const NS_CORE Link& elements )
{
	const auto& elem1 = elements.getElem1();
	const auto& elem2 = elements.getElem2();
	
	if ( elem1 != NS_CORE Element::BRAKE && link->isConsist( elem1 ) )
		link->addElem( elem2 );
	else if ( elem2 != NS_CORE Element::BRAKE && link->isConsist( elem2 ) )
		link->addElem( elem1 );
}


void ari::Scheme::addLink( const std::vector<Cordinate>& trace, const NS_CORE Link& link )
{
	Link_p newLink = Link::create();
	m_links.emplace_back( newLink );

	for ( const auto& it : trace )
		newLink->addCord( it );

	for ( auto & it : m_links )
	{
		addElementsToLink( it, link );
	}
}

void ari::Scheme::addFriction( const std::vector<Cordinate>& trace, const NS_CORE Link& link )
{
	Link_p newLink = Link::create();
	m_links.emplace_back( newLink );

	for ( const auto& it : trace )
		newLink->addCord( it );

	addElementsToLink( newLink, link );
}

void ari::Scheme::clear()
{
	m_links.clear();
}

void ari::Scheme::print( const IDisplay_p& disp ) const
{
	disp->setColors( NS_CORE eColor::YELLOW, NS_CORE eColor::BLACK );
	for ( const auto & it : m_staticElements )
	{
		printElement( it, disp );
	}

	disp->setColors( NS_CORE eColor::GREEN, NS_CORE eColor::BLACK );
	for ( const auto & it : m_links )
	{
		printElement( it, disp );
	}

	disp->resetColors();
	disp->print( { 0, -20 }, '>' );
}
