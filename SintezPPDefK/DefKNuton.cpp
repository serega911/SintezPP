#include "DefKNuton.h"
#include "Equations.h"
#include "Matrix.h"
#include "MatrixOperations.h"

#include "../Libraries/TSingletons.h"

NS_PSS_USING


TK DefKNuton::findK( const TCode& Code, const TI& i, const TK& initialKValues )
{
	
	auto chains = Code.getChains();

	System system;
	system.init( initialKValues );

	auto brakes = Code.getBrakes();

	for ( auto brakeI = 0; brakeI < brakes.size( ); brakeI++ )
	{
		system.addGearChains( chains, brakes[brakeI].getElem1( ), i[brakeI] );
	}

	auto jacobian = createJacobian( system );

	auto gearsN = TSingletons::getInstance()->getNumberOfGears();
	auto gearSetsN = TSingletons::getInstance()->getNumberOfPlanetaryGears();

	const double eps = 0.001;
	const int maxIterCount = 100;
	double norm;

	int iterCount = 0;
	bool notFinded = false;
	do
	{
		auto matrix = createMatrix( jacobian, system );

		MatrixLine rightParts( gearsN *gearSetsN );
		for ( int i = 0; i < gearsN; i++ )
		{
			for ( int j = 0; j < gearSetsN; j++ )
			{
				rightParts[i * gearSetsN + j] = -Equations::wyllys(system.getVariablesSet(i,j));
			}
		}

		auto next = MatrixOperations::solveGaus( matrix, rightParts );

		norm = abs( next[0] );
		for ( int i = 0; i < next.size( ); i++ )
		{
			if ( abs( next[i] ) > norm )
			{
				norm = abs( next[i] );
			}
			system.getUnknownVariables()[i].setValue( system.getUnknownVariables( )[i].getValue( ) + next[i] );
		}

		if ( ++iterCount > maxIterCount )
		{
			notFinded = true;
			break;
		}

	} while ( norm >= eps );


	TK ans( initialKValues );
	if ( !notFinded )
	{
		std::vector<double> kValues;
		for ( auto i = gearSetsN; i < system.getUnknownVariables().size(); i++ )
		{
			kValues.push_back( system.getUnknownVariables()[i].getValue() );
		}
		ans.setValues( kValues );
		ans.setFinded( true );
	}
	else
	{
		ans.setFinded( false );
	}

	return ans;
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
		int a = 5;
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

