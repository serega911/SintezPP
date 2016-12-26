
#include <iostream>

#include "GearSetFactory.h"
#include "Display.h"


void printGearSet( ari::GearSet set, ari::Cordinate anchor )
{
	ari::Display disp;

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

	ari::GearSet set1 = factory.createGearSet( ari::eGearSetType::TYPE_DEFAULT );
	ari::GearSet set2 = factory.createGearSet( ari::eGearSetType::TYPE_N );
	ari::GearSet set3 = factory.createGearSet( ari::eGearSetType::TYPE_N_REVERSE );
	ari::GearSet set4 = factory.createGearSet( ari::eGearSetType::TYPE_U );
	ari::GearSet set5 = factory.createGearSet( ari::eGearSetType::TYPE_U_REVERSE );


	printGearSet( set1, ari::Cordinate( 5, -10 ) );
	printGearSet( set2, ari::Cordinate( 15, -10 ) );
	printGearSet( set3, ari::Cordinate( 25, -10 ) );
	printGearSet( set4, ari::Cordinate( 35, -10 ) );
	printGearSet( set5, ari::Cordinate( 45, -10 ) );

	system( "pause" );
	return 0;
}