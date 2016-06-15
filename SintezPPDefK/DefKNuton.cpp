#include "DefKNuton.h"
#include "Equations.h"
#include "Matrix.h"
#include "MatrixOperations.h"

#include "../Libraries/TSingletons.h"

NS_PSS_USING


TK DefKNuton::findK( TCode& Code )
{
	auto chains = Code.getChains();

	System system;
	system.addGearChains( chains, TElement( eMainElement::EPICYCLIC_GEAR, 1 ), 2 );
	system.addGearChains( chains, TElement( eMainElement::CARRIER, 2 ), 4 );

	auto jacobian = createJacobian( system );

	auto gearsN = TSingletons::getInstance()->getNumberOfGears();
	auto gearSetsN = TSingletons::getInstance()->getNumberOfPlanetaryGears();

	const double eps = 0.001;
	double norm;
	do
	{
		auto matrix = createMatrix( jacobian, system );
		//auto oberMatrix = MatrixOperations::inverse( matrix );

		MatrixLine rightParts( gearsN *gearSetsN );
		for ( int i = 0; i < gearsN; i++ )
		{
			for ( int j = 0; j < gearSetsN; j++ )
			{
				rightParts[i * gearSetsN + j] = -Equations::wyllys(system.getVariablesSet(i,j));
			}
		}

		//auto next = MatrixOperations::multiple( oberMatrix, rightParts );
		auto next = MatrixOperations::solveGaus( matrix, rightParts );

		norm = abs( next[0] );
		for ( int i = 0; i < next.size( ); i++ )
		{
			if ( abs( next[i] ) > norm )
			{
				norm = abs( next[i] );
			}
			system.getUnknownVariables()[i].setValue( system.getUnknownVariables( )[i].getValue( ) - next[i] );
		}


	} while ( norm >= eps );

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

Jacobi DefKNuton::createJacobian( const System & system )
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

Matrix pss::DefKNuton::createMatrix( const Jacobi& jacobian, const System & system )
{
	auto size = jacobian.size();
	
	Matrix ret( size );
	auto undefinedVar = system.getUnknownVariables();

	auto gearsN = TSingletons::getInstance()->getNumberOfGears();
	auto gearSetsN = TSingletons::getInstance()->getNumberOfPlanetaryGears();
	
	for ( auto i = 0; i < gearsN; i++ )
	{
		for ( auto j = 0; j < gearSetsN; j++ )
		{
			for ( auto k = 0; k < undefinedVar.size(); k++ )
			{
				ret.at( i*gearSetsN + j, k ) = jacobian[i*gearSetsN + j][k]( system.getVariablesSet( i, j ) );
			}
		}
	}

	return ret;
}

