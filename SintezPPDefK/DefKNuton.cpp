#include "DefKNuton.h"
#include "Equations.h"
#include "Determinant.h"
#include "UndefinedVariables.h"

#include "../Libraries/TSingletons.h"

pss::TK pss::DefKNuton::findK( pss::TCode& Code )
{
	auto chains = Code.getChains( );

	auto N = TSingletons::getInstance()->getNumberOfPlanetaryGears();

	std::vector<Variables> vectVar = { Variables( N ), Variables( N ) };
	vectVar[0].init( chains, pss::TElement( pss::eMainElement::EPICYCLIC_GEAR, 1 ), 2 );
	vectVar[1].init( chains, pss::TElement( pss::eMainElement::CARRIER, 2 ), 3 );

	UndefinedVariables uVar( vectVar );

	// test
	uVar[0] = 67;
	uVar[1] = 67;
	uVar[2] = 67;
	uVar[3] = 67;

	Determinant det;
	det.setSize( 2 );
	value ans = det[1][1](1,2,3,4);

	return TK( 1 );
}

void pss::DefKNuton::run()
{
	pss::TSingletons::getInstance( )->setGlobalParameters( 2, 2 );

	pss::TCode code;
	code.setIn( pss::TElement( pss::eMainElement::CARRIER, 1 ) );
	code.setOut( pss::TElement( pss::eMainElement::SUN_GEAR, 2 ) );
	code.setLinks( {
		pss::TLink( pss::TElement( pss::eMainElement::SUN_GEAR, 1 ), pss::TElement( pss::eMainElement::CARRIER, 2 ) ),
		pss::TLink( pss::TElement( pss::eMainElement::EPICYCLIC_GEAR, 1 ), pss::TElement( pss::eMainElement::EPICYCLIC_GEAR, 2 ) )
	} );
	code.setBrakes( {
		pss::TLink( pss::TElement( pss::eMainElement::EPICYCLIC_GEAR, 1 ), pss::TElement::BRAKE ),
		pss::TLink( pss::TElement( pss::eMainElement::CARRIER, 2 ), pss::TElement::BRAKE )
	} );

	m_i.push_back(3);
	m_i.push_back(4);

	findK( code );
}