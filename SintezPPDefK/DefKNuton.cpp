#include "DefKNuton.h"
#include "Equations.h"
#include "Matrix.h"
#include "MatrixOperations.h"
#include "../Libraries/TGearChanger.h"

#include "../Libraries/TSingletons.h"

NS_PSS_USING


TK DefKNuton::findK( const TCode& Code, const TK& initialKValues )
{
	
	auto chains = Code.getChains();

	System system;
	system.init( initialKValues );

	int i = 0;
	TGearChanger gearChanger( Code );
	do 
	{
		system.addGearChains( chains, gearChanger.getDrivingElementsForGear(i+1)[0].getElem1(), TSingletons::getInstance()->getInitialData()._i[i] );
		i++;
	} while ( gearChanger.next() );

	auto jacobian = createJacobian( system );

	const auto& initialData = TSingletons::getInstance()->getInitialData();

	const double eps = 0.001;
	const int maxIterCount = 100;
	double norm;

	int iterCount = 0;
	bool notFinded = false;
	do
	{
		auto matrix = createMatrix( jacobian, system );

		MatrixLine rightParts( initialData._numberOfGears *initialData._numberOfPlanetaryGears );
		for ( int i = 0; i < initialData._numberOfGears; i++ )
		{
			for ( int j = 0; j < initialData._numberOfPlanetaryGears; j++ )
			{
				rightParts[i * initialData._numberOfPlanetaryGears + j] = -Equations::wyllys( system.getVariablesSet( i, j ) );
			}
		}

		auto next = MatrixOperations::solveGaus( matrix, rightParts );

		if ( next.size() == 0 )
		{
			notFinded = true;
			break;
		}

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


		for ( auto i = 0; i < initialData._numberOfPlanetaryGears; i++ )
		{
			bool flag = false;
			for ( auto j = 0; j < initialData._ranges.size(); j++ )
			{
				if ( initialData._ranges[j].isInRange( system.getUnknownVariables()[i].getValue() ) )
				{
					flag = true;
					break;
				}
			}
			if ( !flag )
			{
				notFinded = true;
				break;
			}

		}

		if ( notFinded )
		{
			break;
		}

	} while ( norm >= eps );


	TK ans( initialKValues );
	if ( !notFinded )
	{
		std::vector<double> kValues;
		for ( auto i = 0; i < initialData._numberOfPlanetaryGears; i++ )
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

	const auto& initialData = TSingletons::getInstance()->getInitialData();

	if ( initialData._numberOfGears * initialData._numberOfPlanetaryGears == undefinedVar.size() )
	{
		det.setSize( initialData._numberOfGears * initialData._numberOfPlanetaryGears );
		for ( auto i = 0; i < initialData._numberOfGears; i++ )
		{
			for ( auto j = 0; j < initialData._numberOfPlanetaryGears; j++ )
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
							det.setEquation( i*initialData._numberOfPlanetaryGears + j, k, eq );
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

	const auto& initialData = TSingletons::getInstance()->getInitialData();
	
	for ( auto i = 0; i < initialData._numberOfGears; i++ )
	{
		for ( auto j = 0; j < initialData._numberOfPlanetaryGears; j++ )
		{
			for ( auto k = 0; k < undefinedVar.size(); k++ )
			{
				ret.at( i*initialData._numberOfPlanetaryGears + j, k ) = jacobian[i*initialData._numberOfPlanetaryGears + j][k]( system.getVariablesSet( i, j ) );
			}
		}
	}

	return ret;
}

