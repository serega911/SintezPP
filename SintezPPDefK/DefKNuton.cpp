#include "DefKNuton.h"
#include "Equations.h"
#include "Matrix.h"
#include "MatrixOperations.h"

#include "../Libraries/TSingletons.h"

NS_PSS_USING

void ober_matr( double a[2][2] )
{
	double det, aa;
	det = a[0][0] * a[1][1] - a[0][1] * a[1][0];
	aa = a[0][0];
	a[0][0] = a[1][1] / det;
	a[1][1] = aa / det;
	aa = a[0][1];
	a[0][1] = -a[0][1] / det;
	a[1][0] = -a[1][0] / det;
}

TK DefKNuton::findK( TCode& Code )
{
	auto chains = Code.getChains();

	System system;
	system.addGearChains( chains, TElement( eMainElement::EPICYCLIC_GEAR, 1 ), 2 );
	system.addGearChains( chains, TElement( eMainElement::CARRIER, 2 ), 4 );

	auto determinant = createDeterminant( system );

	Matrix matr( {
		{ 1, 0, 1, 5 },
		{ 8, 1, -4, -7 },
		{ 0, -3, 4, 6 },
		{ 2, 6, 8, -7 },
	} );



	auto det = MatrixOperations::convertToInversMatrix(matr);

	//a[2][2] - determinant
	//b[2] - values of wyllys

// 	int i = 1;
// 	const double eps = 0.001;
// 	double dx, dy, norm;
// 	do
// 	{
// 		ober_matr( a );
// 		dx = -a[0][0] * function1( x, y ) + -a[0][1] * function2( x, y );
// 		dy = -a[1][0] * function1( x, y ) + -a[1][1] * function2( x, y );
// 		x = x + dx;
// 		y = y + dy;
// 		b[0] = function1( x, y );
// 		b[1] = function2( x, y );
// 		norm = sqrt( b[0] * b[0] + b[1] * b[1] );
// 		i++;
// 	} while ( norm >= eps );

	return TK( 1 );
}

void DefKNuton::run()
{
	TSingletons::getInstance( )->setGlobalParameters( 2, 2 );

	TCode code;
	code.setIn( TElement( eMainElement::CARRIER, 1 ) );
	code.setOut( TElement( eMainElement::SUN_GEAR, 2 ) );
	code.setLinks( {
		TLink( TElement( eMainElement::SUN_GEAR, 1 ), TElement( eMainElement::CARRIER, 2 ) ),
		TLink( TElement( eMainElement::EPICYCLIC_GEAR, 1 ), TElement( eMainElement::EPICYCLIC_GEAR, 2 ) )
	} );
	code.setBrakes( {
		TLink( TElement( eMainElement::EPICYCLIC_GEAR, 1 ), TElement::BRAKE ),
		TLink( TElement( eMainElement::CARRIER, 2 ), TElement::BRAKE )
	} );

	m_i.push_back(3);
	m_i.push_back(4);

	findK( code );
}

Jacobi DefKNuton::createDeterminant( const System & system )
{
	Jacobi det;
	
	auto undefinedVar = system.getUnknownVariables();

	auto gearsN = TSingletons::getInstance()->getNumberOfGears();
	auto gearSetsN = TSingletons::getInstance()->getNumberOfPlanetaryGears();

	if ( gearsN * gearSetsN == undefinedVar.size() )
	{
		det.setSize( gearsN * gearSetsN );
		for ( auto i = 0; i < gearsN; i++ )
		{
			for ( auto j = 0; j < gearSetsN; j++ )
			{
				for ( auto k = 0; k < undefinedVar.size(); k++ )
				{
					auto undefVarListeners = undefinedVar[k].getAllListeners();
					auto gearSetVariables = system.getVariablesSet( i, j );
					for ( const auto & variable : undefVarListeners )
					{
						if ( ( !gearSetVariables[variable->getElement().getElemN()].getDefined() ) && variable->getElement().getGearSetN() == j + 1 )
						{
							auto eq = Equations::getEquation( variable->getElement().getElemN() );
							det.setEquation( i*gearSetsN + j, k, eq );
						}
					}
				}
			}
		}
	}
	else
	{
		//exception
	}
	return det;
}

