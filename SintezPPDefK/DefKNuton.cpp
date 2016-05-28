#include "DefKNuton.h"
#include "Equations.h"
#include "Determinant.h"

#include "../Libraries/TSingletons.h"

void pss::DefKNuton::defineVariables( pss::Variables& var, pss::TCode& Code )
{
	auto chains = Code.getChains();
	static std::vector<double> vectW;
	static std::vector<double> wOut;
	static variable inputW = 1.0;
	
	// i
	for ( int i = 0; i < m_i.size(); i++ )
		wOut.push_back( 1 / m_i[i] );

	for ( auto& chain: chains )
	{
		if ( chain.find( pss::TElement::INPUT ) )
		{
			const auto& elements = chain.getElements();
			for ( auto& elem : elements )
			{
				if ( elem != pss::TElement::INPUT )
				{
					int gearSetN = elem.getGearSetN();
					int elemN = elem.getElemN()._to_integral();
					var[gearSetN - 1][elemN]._def = true;
					var[gearSetN - 1][elemN]._var = &inputW;
				}

			}
		}
	}

}

pss::TK pss::DefKNuton::findK( pss::TCode& Code )
{
	Variables variables(TSingletons::getInstance()->getNumberOfPlanetaryGears());
	
	defineVariables( variables, Code );

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