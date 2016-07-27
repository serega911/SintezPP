#include "DefKNuton.h"
#include "Equations.h"
#include "Matrix.h"
#include "MatrixOperations.h"
#include "../Libraries/TGearChanger.h"

#include "../Libraries/TSingletons.h"

#include <iostream>

NS_PSS_USING


TK DefKNuton::findK( const TCode& Code, const TK& initialKValues, const TI& iTarget )
{
	System system;
	system.init( initialKValues );

	TGearChanger gearChanger( Code );
	int i = 0;
	do 
	{
		system.addGearChains( Code.getChains(), gearChanger.getDrivingElementsForGear( i + 1 ), i + 1, iTarget[i] );
		i++;
	} while ( gearChanger.next() );

	auto jacobian = createJacobian( system );

	const double eps = 0.001;
	const int maxIterCount = 100;
	double norm;
	int iterCount = 0;
	bool notFinded = false;

	TK ans( initialKValues );

	//TLog::log( "|", false );
	do
	{
		//TLog::log( ".", false );
		// создаем матрицу с уравнениями
		auto matrix = createMatrix( jacobian, system );
		// создаем вектор правых частей уравнений
		auto rightParts = createRightParts( system );
		// решаем систему уравнений и получаем дельту
		auto next = MatrixOperations::solveGaus( matrix, rightParts );
		// если решений нет - прерываемся, иначе вычисляем начальные условия для следующей итерации
		if ( next.size() == 0 || ++iterCount > maxIterCount )
		{
			notFinded = true;
		}
		else
		{
			// вычисляем норму ( максимальную дельту )
			norm = calcNorm( next );
			// вычисляем начальные значения для следующей итерации
			for ( int i = 0; i < next.size(); i++ )
			{
				system.getUnknownVariables()[i].setValue( system.getUnknownVariables()[i].getValue() + next[i] );
			}
			// проверяем полученные значения К на попадания в заданные диапазоны
			ans = getKValuesFromSystem( system );
			notFinded = !ans.check();
		}
	} while ( !notFinded && norm >= eps );

	ans.setFinded( !notFinded );
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
						if ( ( !gearSetVariables[variable->getElement().getElemN()].getDefined() ) && variable->getElement().getGearSetN() == j + 1 && variable->getGear() == i + 1 )
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

double pss::DefKNuton::calcNorm( const MatrixLine& delta )
{
	double norm = abs( delta[0] );

	for ( int i = 0; i < delta.size(); i++ )
	{
		if ( abs( delta[i] ) > norm )
		{
			norm = abs( delta[i] );
		}
	}

	return norm;
}

pss::TK pss::DefKNuton::getKValuesFromSystem( const System & system )
{
	const auto& initialData = TSingletons::getInstance()->getInitialData();

	std::vector<double> kValues;
	for ( auto i = 0; i < initialData._numberOfPlanetaryGears; i++ )
	{
		kValues.push_back( system.getUnknownVariables()[i].getValue() );
	}
	
	TK ret;
	ret.setValues( kValues );

	return ret;
}

pss::MatrixLine pss::DefKNuton::createRightParts( const System & system )
{
	const auto& initialData = TSingletons::getInstance()->getInitialData();

	MatrixLine rightParts( initialData._numberOfGears *initialData._numberOfPlanetaryGears );
	for ( int i = 0; i < initialData._numberOfGears; i++ )
	{
		for ( int j = 0; j < initialData._numberOfPlanetaryGears; j++ )
		{
			rightParts[i * initialData._numberOfPlanetaryGears + j] = -Equations::wyllys( system.getVariablesSet( i, j ) );
		}
	}

	return rightParts;
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

