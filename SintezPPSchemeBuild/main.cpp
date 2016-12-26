
#include <iostream>

#include "GearSetFactory.h"
#include "Display.h"


void printGearSet( ari::GearSet set )
{
	ari::Display disp;
	ari::Cordinate anchor = set.getAnchor();

	const auto& cords = set.get();

	for ( const auto& it : cords )
	{
		char c;
		switch ( it._element )
		{
		case NS_CORE eMainElement::SUN_GEAR: c = 'S'; break;
		case NS_CORE eMainElement::EPICYCLIC_GEAR: c = 'E'; break;
		case NS_CORE eMainElement::CARRIER: c = 'C'; break;
		default: c = '#'; break;
		}
		disp.print( it._cord + anchor, c );
	}

	disp.print( {0, -20}, '>' );
}


int main()
{
	ari::GearSetFactory factory;

	ari::GearSet set1 = factory.createGearSet( ari::eGearSetType::TYPE_N_REVERSE );
	set1.setAnchor( ari::Cordinate( 5, -10 ) );

	printGearSet( set1 );

	system( "pause" );
	return 0;
}