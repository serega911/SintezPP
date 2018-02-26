#include "DefKNuton.h"
#include "Equations.h"
#include "Matrix.h"
#include "MatrixOperations.h"
#include "CheckAllPossibilities.h"
#include "../Libraries/GearBoxWithChanger.h"
#include "../Libraries/Singletons.h"

#include <iostream>

NS_ARI_USING

NS_CORE InternalGearRatioArray DefKNuton::calculate( const NS_CORE Code& code )
{
	//NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K_NUTON, code );

	const auto size = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	NS_CORE InternalGearRatios initial;
	NS_CORE InternalGearRatioArray ans;

	auto calcFuncPrenum = [&]( const NS_CORE Ratios& curI ) -> bool
	{
		NS_CORE InternalGearRatios k = findK( code, initial, curI );

		if ( k.size() > 0 )
		{
			ans.emplace_back( k );
			//if ( k.check() )
			//NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K_NUTON, k );
		}

		return true;
	};

	auto calcFuncK = [&]( const NS_CORE InternalGearRatios& init ) -> bool
	{
		initial = init;
		CheckAllPossibilities::checkAllRatiosPermutations( calcFuncPrenum );

		return true;
	};

	CheckAllPossibilities::checkAllInitialKValues( calcFuncK );

	return ans;
}

NS_CORE InternalGearRatios DefKNuton::findK( const NS_CORE Code& code, const NS_CORE InternalGearRatios& initialKValues, const NS_CORE Ratios& iTarget )
{
	System system;
	system.init( initialKValues );

	NS_CORE GearBoxWithChanger gb( code );
	gb.createChains();

	int i = 0;
	do
	{
		system.addGearChains( gb.getChainsForCurrentGear(), NS_CORE GearNumber( i + 1 ), iTarget[i] );
		i++;
	} while ( gb.turnOnNextGear() );

	auto jacobian = createJacobian( system );

	return solveNuton( jacobian, system );
}

Jacobi DefKNuton::createJacobian( const System & system )
{
	Jacobi det;

	auto undefinedVar = system.getUnknownVariables();

	const auto& initialData = NS_CORE Singletons::getInstance()->getInitialData();

	if ( initialData._numberOfGears * initialData._numberOfPlanetaryGears == undefinedVar.size() )
	{
		det.setSize( initialData._numberOfGears * initialData._numberOfPlanetaryGears );
		for ( size_t i = 0; i < initialData._numberOfGears; i++ )
		{
			for ( size_t j = 0; j < initialData._numberOfPlanetaryGears; j++ )
			{
				for ( size_t k = 0; k < undefinedVar.size(); k++ )
				{
					auto undefVarListeners = undefinedVar[k].getAllListeners();
					auto gearSetVariables = system.getVariablesSet( NS_CORE GearNumber( i ), j );
					for ( const auto & variable : undefVarListeners )
					{
						if ( ( !gearSetVariables[variable->getElement().getElemN()].getDefined() ) && variable->getElement().getGearSetN().getValue() == j + 1 && variable->getGear() == NS_CORE GearNumber( i + 1 ) )
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

double DefKNuton::calcNorm( const MatrixLine& delta )
{
	double norm = abs( delta[0] );

	for ( size_t i = 0; i < delta.size(); i++ )
	{
		if ( abs( delta[i] ) > norm )
		{
			norm = abs( delta[i] );
		}
	}

	return norm;
}

NS_CORE InternalGearRatios DefKNuton::solveNuton( const Jacobi& jacobian, System& system )
{
	const double eps = 0.001;
	const int maxIterCount = 100;
	double norm;
	int iterCount = 0;
	bool notFinded = false;

	do
	{
		// создаем матрицу с уравнениями
		auto matrix = createMatrix( jacobian, system );
		// создаем вектор правых частей уравнений
		auto rightParts = createRightParts( system );
		// решаем систему уравнений и получаем дельту
		auto next = MatrixOperations::solveGaus( matrix, rightParts );
		if ( next.size() == 0 )
		{
			next = MatrixOperations::solveKramer( matrix, rightParts );
		}
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
			for ( size_t i = 0; i < next.size(); i++ )
			{
				system.getUnknownVariables()[i].setValue( system.getUnknownVariables()[i].getValue() + next[i] );
			}
		}
	} while ( !notFinded && norm >= eps );

	NS_CORE InternalGearRatios ans;
	if ( !notFinded )
	{
		ans = geInternalGearRatioValuesFromSystem( system );
	}

	return ans;
}

NS_CORE InternalGearRatios DefKNuton::geInternalGearRatioValuesFromSystem( const System & system )
{
	const auto& initialData = NS_CORE Singletons::getInstance()->getInitialData();

	NS_CORE InternalGearRatioValueArray kValues;
	for ( size_t i = 0; i < initialData._numberOfPlanetaryGears; i++ )
	{
		kValues.push_back( NS_CORE InternalGearRatioValue( system.getUnknownVariables()[i].getValue() ) );
	}

	NS_CORE InternalGearRatios ret;
	ret.setValues( kValues );

	return ret;
}

MatrixLine DefKNuton::createRightParts( const System & system )
{
	const auto& initialData = NS_CORE Singletons::getInstance()->getInitialData();

	MatrixLine rightParts( initialData._numberOfGears *initialData._numberOfPlanetaryGears );
	for ( size_t i = 0; i < initialData._numberOfGears; i++ )
	{
		for ( size_t j = 0; j < initialData._numberOfPlanetaryGears; j++ )
		{
			rightParts[i * initialData._numberOfPlanetaryGears + j] = -Equations::wyllys( system.getVariablesSet( NS_CORE GearNumber( i ), j ) );
		}
	}

	return rightParts;
}

Matrix DefKNuton::createMatrix( const Jacobi& jacobian, const System & system )
{
	auto size = jacobian.size();

	Matrix ret( size );
	auto undefinedVar = system.getUnknownVariables();

	const auto& initialData = NS_CORE Singletons::getInstance()->getInitialData();

	for ( size_t i = 0; i < initialData._numberOfGears; i++ )
	{
		for ( size_t j = 0; j < initialData._numberOfPlanetaryGears; j++ )
		{
			for ( size_t k = 0; k < undefinedVar.size(); k++ )
			{
				ret.at( i*initialData._numberOfPlanetaryGears + j, k ) = jacobian[i*initialData._numberOfPlanetaryGears + j][k]( system.getVariablesSet( NS_CORE GearNumber( i ), j ) );
			}
		}
	}

	return ret;
}

