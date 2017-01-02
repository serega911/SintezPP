
#include <iostream>

#include "GearSetFactory.h"
#include "ISchemeElement.h"
#include "GearSet.h"
#include "Display.h"


void printGearSet( NS_ARI ISchemeElement_p set )
{
	ari::Display disp;

	const auto& cords = set->getCordsWorldSpace();

	for ( const auto& it : cords )
	{
		char c;

		if ( it->isConsist( NS_CORE eMainElement::SUN_GEAR ) )
			c = 'S';
		else if ( it->isConsist( NS_CORE eMainElement::EPICYCLIC_GEAR ) )
			c = 'E';
		else if ( it->isConsist( NS_CORE eMainElement::CARRIER ) )
			c = 'C';
		else 
			c = '#';
		
		disp.print( it->getCord(), c );
	}

	disp.print( {0, -20}, '>' );
}


int main()
{
	ari::GearSetFactory factory;
	std::vector<NS_ARI ISchemeElement_p> sets;
	const ari::Cordinate delta( 10, 0 );
	ari::Cordinate pos( 5, -10 );
	const ari::eGearSetType types[] = { 
		ari::eGearSetType::TYPE_DEFAULT, 
		ari::eGearSetType::TYPE_N, 
		ari::eGearSetType::TYPE_N_REVERSE, 
		ari::eGearSetType::TYPE_U, 
		ari::eGearSetType::TYPE_U_REVERSE };

	

	for ( const auto & it : types )
	{
		std::shared_ptr<ari::ISchemeElement> set = factory.createGearSet( it, pos );
		sets.emplace_back( set );
		pos = pos + delta;
	}


	for ( const auto & it : sets )
	{
		printGearSet( it );
	}

	system( "pause" );
	return 0;
}