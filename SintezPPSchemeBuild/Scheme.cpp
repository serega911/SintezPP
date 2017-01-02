#include "Scheme.h"
#include "GearSetFactory.h"

#include "../Libraries/Singletons.h"

NS_ARI_USING

const int Scheme::s_setWidth = 9;
const int Scheme::s_height = 13;



void ari::Scheme::printElement( NS_ARI ISchemeElement_p set, const Display& disp )
{
	const auto& cords = set->getCordsWorldSpace();

	for ( const auto& it : cords )
	{
		char c;

		if ( it->isConsist( NS_CORE eMainElement::INPUT ) )
			c = 'I';
		else if ( it->isConsist( NS_CORE eMainElement::OUTPUT ) )
			c = 'O';
		else if ( it->isConsist( NS_CORE eMainElement::BRAKE ) )
			c = 'B';
		else if( it->isConsist( NS_CORE eMainElement::SUN_GEAR ) )
			c = 'S';
		else if ( it->isConsist( NS_CORE eMainElement::EPICYCLIC_GEAR ) )
			c = 'E';
		else if ( it->isConsist( NS_CORE eMainElement::CARRIER ) )
			c = 'C';
		else
			c = '#';

		disp.print( it->getCord(), c );
	}

	disp.print( { 0, -20 }, '>' );
}

Scheme::Scheme( const NS_CORE InternalGearRatios k )
{
	const int count = k.size();

	m_width = count * s_setWidth;
	const ari::Cordinate delta( s_setWidth, 0 );
	ari::Cordinate pos( s_setWidth / 2, - s_height / 2 );

	for ( int i = 0; i < count; i++ )
	{
		m_staticElements.emplace_back( GearSetFactory::createGearSet( k[i], pos ) );
		pos = pos + delta;
	}

	Link_p brake = Link::create();
	brake->addElem( NS_CORE eMainElement::BRAKE );
	for ( int i = 0; i < m_width; i++ )
	{	
		brake->addCord( Cordinate( i, 0 ) );
	}
	m_staticElements.emplace_back( brake );

	Link_p input = Link::create();
	input->addElem( NS_CORE eMainElement::INPUT );
	input->addCord( Cordinate( 0, -s_height + 1 ) );
	m_staticElements.emplace_back( input );

	Link_p output = Link::create();
	output->addElem( NS_CORE eMainElement::OUTPUT );
	output->addCord( Cordinate( m_width - 1, -s_height + 1 ) );
	m_staticElements.emplace_back( output );
}

void ari::Scheme::addLink( const std::vector<Cordinate>& trace, const NS_CORE Link& link )
{
	Link_p newLink = Link::create();

	for ( const auto& it : trace )
		newLink->addCord( it );

	m_links.emplace_back( newLink );
}

void ari::Scheme::clear()
{
	m_links.clear();
}

void ari::Scheme::print( const Display& disp )
{
	for ( const auto & it : m_staticElements )
	{
		printElement( it, disp );
	}

	for ( const auto & it : m_links )
	{
		printElement( it, disp );
	}
}
