#include "DefKNuton.h"
#include "Equations.h"
#include "Matrix.h"
#include "MatrixOperations.h"
#include "../Libraries/TGearChanger.h"

#include "../Libraries/TSingletons.h"

#include <iostream>

NS_ARI_USING


NS_CORE TK DefKNuton::findK( const NS_CORE TGearBox& gearBox, const NS_CORE TK& initialKValues, const NS_CORE TI& iTarget )
{
    System system;
    system.init( initialKValues );

    NS_CORE TGearBox gb( gearBox );

    int i = 0;
    do 
    {
        system.addGearChains( gb.getChainsForCurrentGear(), i + 1, iTarget[i] );
        i++;
    } while ( gb.turnOnNextGear() );

    auto jacobian = createJacobian( system );

	return solveNuton( jacobian, system );
	//return solveSimple( system );
}

Jacobi DefKNuton::createJacobian( const System & system )
{
    Jacobi det;
    
    auto undefinedVar = system.getUnknownVariables();

    const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();

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

double DefKNuton::calcNorm( const MatrixLine& delta )
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

NS_CORE TK ari::DefKNuton::solveSimple( System& system )
{
	const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();
	const auto elements = { NS_CORE eMainElement::SUN_GEAR, NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE eMainElement::CARRIER, NS_CORE eMainElement::EMPTY };

	for ( int k = 0; k < initialData._numberOfGears * initialData._numberOfPlanetaryGears; k++ )
	{
		for ( int i = 0; i < initialData._numberOfGears; i++ )
		{
			for ( int j = 0; j < initialData._numberOfPlanetaryGears; j++ )
			{
				auto& gearSetVariables = system.getVariablesSet( i, j );

				NS_CORE eMainElement undefElem;
				size_t count = 0;

				//считаем количество неизвестных в уравнении
				for ( const auto & elem : elements )
				{
					if ( gearSetVariables[elem].getDefined() == false )
					{
						count++;
						undefElem = elem;
					}
				}

				//если неизвестное одно - можем его найти
				VariableValue value;
				if ( 1 == count )
				{
					value = Equations::calcOne( undefElem, gearSetVariables );
					//отмечаем как известное
					auto& unknowns = system.getUnknownVariables();

					for ( auto& unknown : unknowns )
					{
						if ( unknown.findElementInListeners( NS_CORE TElement( undefElem, j + 1 ), i + 1 ) )
						{
							unknown.setLastValue( value );
						}
					}
				}
			}
		}
	}

	NS_CORE TK ans = getKValuesFromSystem( system );
	ans.setFinded( true );
	return ans;
}

NS_CORE TK ari::DefKNuton::solveNuton( const Jacobi& jacobian, System& system )
{
	const double eps = 0.001;
	const int maxIterCount = 100;
	double norm;
	int iterCount = 0;
	bool notFinded = false;

	NS_CORE TK ans;

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
			for ( size_t i = 0; i < next.size(); i++ )
			{
				system.getUnknownVariables()[i].setValue( system.getUnknownVariables()[i].getValue() + next[i] );
			}
			// проверяем полученные значения К на попадания в заданные диапазоны
			ans = getKValuesFromSystem( system );
			notFinded = ( !ans.check() && !( iterCount < 10 ) );

		}
	} while ( !notFinded && norm >= eps );

	ans.setFinded( !notFinded && ans.check() );
	return ans;
}

NS_CORE TK DefKNuton::getKValuesFromSystem( const System & system )
{
    const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();

    std::vector<double> kValues;
    for ( auto i = 0; i < initialData._numberOfPlanetaryGears; i++ )
    {
        kValues.push_back( system.getUnknownVariables()[i].getValue() );
    }
    
    NS_CORE TK ret;
    ret.setValues( kValues );

    return ret;
}

MatrixLine DefKNuton::createRightParts( const System & system )
{
    const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();

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

Matrix DefKNuton::createMatrix( const Jacobi& jacobian, const System & system )
{
    auto size = jacobian.size();
    
    Matrix ret( size );
    auto undefinedVar = system.getUnknownVariables();

    const auto& initialData = NS_CORE TSingletons::getInstance()->getInitialData();
    
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

