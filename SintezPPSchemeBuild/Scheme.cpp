#include <algorithm>
#include <iterator>

#include "Scheme.h"
#include "GearSetFactory.h"
#include "Display.h"

#include "../Libraries/eColor.h"
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

void ari::Scheme::mergeLinks()
{
	const int size = m_links.size();
	
	bool flag = false;
	do 
	{
		flag = false;
		for ( int i = 0; i < size; i++ )
		{
			for ( int j = 0; j < size; j++ )
			{
				const auto& elems1 = m_links[i]->getElements();
				const auto& elems2 = m_links[j]->getElements();

				if ( i != j && elems1 != elems2 && elems1.intersect( elems2 ) )
				{
					m_links[i]->addChain( elems2 );
					m_links[j]->addChain( m_links[i]->getElements() );
					flag = true;
				}
			}
		}
	} while (flag);
	
}

Scheme::Scheme( const NS_CORE InternalGearRatios k )
{
	const int count = k.size();

	m_width = count * s_setWidth;
	const ari::Cordinate delta( s_setWidth, 0 );
	ari::Cordinate pos( s_setWidth / 2, s_height / 2 );

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
	input->addCord( Cordinate( 0, s_height - 1 ) );
	m_staticElements.emplace_back( input );

	Link_p output = Link::create();
	output->addElem( NS_CORE Element::OUTPUT );
	output->addCord( Cordinate( m_width - 1, s_height - 1 ) );
	m_staticElements.emplace_back( output );
}

size_t ari::Scheme::getHeight() const
{
	return s_height;
}

size_t ari::Scheme::getWidth() const
{
	return m_width;
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




void ari::Scheme::addLink( const std::vector<Cordinate>& trace, const NS_CORE Link& link )
{
	Link_p newLink = Link::create();
	m_links.emplace_back( newLink );

	for ( const auto& it : trace )
		newLink->addCord( it );

	if ( link.getElem2() != NS_CORE Element::BRAKE)
		newLink->addLink( link );
	else
		newLink->addElem( link.getElem1() );

	mergeLinks();
}

void ari::Scheme::addFriction( const std::vector<Cordinate>& trace, const NS_CORE Link& link )
{
	Link_p firstHalf = Link::create();
	Link_p secondHalf = Link::create();

	m_links.emplace_back( firstHalf );
	m_links.emplace_back( secondHalf );

	firstHalf->addElem( link.getElem1() );
	secondHalf->addElem( link.getElem2() );

	const int size = trace.size();
	int i = 0;
	for ( int i = 0; i < size/2; i++ )
		firstHalf->addCord( trace[i] );
	for ( ; i < size; i++ )
		secondHalf->addCord( trace[i] );

}

void ari::Scheme::clear()
{
	m_links.clear();
}

void ari::Scheme::print( const IDisplay_p& disp ) const
{
	system( "cls" );

	std::vector<NS_CORE Chain> uniqueChains;
	for ( const auto & it : m_links )
	{
		uniqueChains.emplace_back( it->getElements() );
	}
	
	std::vector<NS_CORE Chain, std::allocator<NS_CORE Chain>>::iterator it;
	it = std::unique( uniqueChains.begin(), uniqueChains.end() );
	uniqueChains.erase( it, uniqueChains.end() );

	disp->setColors( NS_CORE eColor::YELLOW, NS_CORE eColor::BLACK );
	for ( const auto & it : m_staticElements )
	{
		printElement( it, disp );
	}

	for ( const auto & it : m_links )
	{
		int i = 1;
		for ( i = 1; i < uniqueChains.size() && i < NS_CORE colorsCount - 1; i++ )
		{
			if ( it->getElements() == uniqueChains[i] )
				break;
		}
		NS_CORE eColor color = NS_CORE colors[i];

		disp->setColors( color, NS_CORE eColor::BLACK );
		printElement( it, disp );
	}

	disp->resetColors();
	disp->print( { 0, 20 }, '>' );

	system( "pause" );
}
