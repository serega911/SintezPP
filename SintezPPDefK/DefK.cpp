#include "DefK.h"
#include "DefKNuton.h"
#include "../Libraries/func_lib.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TGaus.h"
#include "../Libraries/TCombinations.h"
#include "../Libraries/TGearChanger.h"
#include "../Libraries/TLog.h"

#include <algorithm>
#include <iostream>

NS_ARI_USING


void DefK::readInitialData()
{
	setlocale( LC_ALL, "Russian" );

	NS_CORE TLog::log( "====  Синтез планетарных передач с тремя степенями свободы. Определение К.  ====" );

	//	Исходные данные
	int W;
	int N;
	NS_CORE TLog::log( "\t\t\tИсходные данные." );
	NS_CORE TLog::log( "Число степеней свободы:	", false );
	std::cin >> W;
	NS_CORE TLog::log( "Количество ПМ:		", false );
	std::cin >> N;
	NS_CORE TSingletons::getInstance()->setGlobalParameters( W, N );

	int countIntervals = 0;
	NS_CORE TLog::log( "Количество диапазонов : ", false );
	std::cin >> countIntervals;
	for ( int i = 0; i < countIntervals; i++ )
	{
		double beg, end;
		NS_CORE TLog::log( "Начало диапазона:	", false );
		std::cin >> beg;
		NS_CORE TLog::log( "Конец диапазона:	", false );
		std::cin >> end;
		NS_CORE TSingletons::getInstance()->addRangeK( NS_CORE TRange( beg, end ) );
	}
	NS_CORE TLog::log( "Передаточные отношения:	", false );
	for ( int i = 0; i < NS_CORE TSingletons::getInstance()->getInitialData()._numberOfGears; i++ )
	{
		double ratio = 0;
		std::cin >> ratio;
		if ( ratio != 0 )
			NS_CORE TSingletons::getInstance()->addGearRatio( ratio );
		else
			break;
	}
}

void DefK::run()
{ 
	readInitialData();

	NS_CORE TCode code;
	while ( NS_CORE TSingletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE TIOFileManager::eOutputFileType::DONE, code ) )
	{
		NS_CORE TGearBox gearBox( code );
		gearBox.createChains();
		NS_CORE TK ans( findK( gearBox ) );
		
		if (ans.getFinded())
		{
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, code );
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, ans );
			//TLog::log( "+", false );
		}
		//TLog::log( "" );
	}
}

NS_CORE TK DefK::findK( const NS_CORE TGearBox& gearBox )
{
	NS_CORE TK ans;

	checkAllInitialKValues( gearBox, ans );

	return ans;
}

void DefK::checkAllInitialKValues( const NS_CORE TGearBox& gearBox, NS_CORE TK& ret )
{

	std::vector<int> combi;
	for ( auto i = 0; i < NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears; i++ )
		combi.push_back( 0 );

	do{

		std::vector<double> initialK;
		for ( auto i = 0; i < combi.size(); i++ )
			initialK.push_back( NS_CORE TSingletons::getInstance()->getInitialData()._ranges[combi[i]].getMid() );

		NS_CORE TK initial;
		initial.setValues( initialK );

		checkAllRatiosPermutations( gearBox, initial, ret );

	} while ( !ret.getFinded() && NS_CORE next_combination_repetition( combi, NS_CORE TSingletons::getInstance()->getInitialData()._ranges.size() - 1, 0 ) );
}

void DefK::checkAllRatiosPermutations( const NS_CORE TGearBox& gearBox, const NS_CORE TK& initial, NS_CORE TK& ret )
{
	NS_CORE TI iTarget = NS_CORE TSingletons::getInstance()->getInitialData()._i;

	std::vector<int> replace;
	for ( int i = 0; i < iTarget.size(); i++ )
		replace.push_back( i );

	do{

		std::vector<double> curI;
		for ( int i = 0; i < iTarget.size(); i++ )
			curI.push_back( iTarget[replace[i]] );

		NS_ARI DefKNuton defKByNonlinearSolving;
		ret = defKByNonlinearSolving.findK( gearBox, initial, NS_CORE TI( curI, 0.1 ) );

	} while ( !ret.getFinded() && std::next_permutation( replace.begin(), replace.end() ) );
}

//==================================================================================================================================================================
//==================================================================================================================================================================
//==================================================================================================================================================================
NS_CORE TK DefK::findK( const NS_CORE TCode& Code, NS_CORE TK K )
{
	do{
		//K.print();
		if ( podModul( Code, K ) )
		{
			K.setFinded();
			break;
		}
		//system("pause");
	} while ( K.next() );
	return K;
}

void DefK::run()
{
	NS_CORE TCode code;
	while ( NS_CORE TSingletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE TIOFileManager::eOutputFileType::DONE, code ) )
	{
		NS_CORE TK ans( findK( code, K ) );
		if ( ans.getFinded() )
		{
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, code );
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, ans );
		}
	}
}

bool DefK::podModul( const NS_CORE TCode & code, const NS_CORE TK &k )
{
	NS_CORE TGearChanger gearChanger( code );
	NS_CORE TI tmpI( {}, 0.01 );	//вектор для полученных передаточных отношений при данном наборе K
	do
	{
		NS_CORE TGaus gaus;
		gaus.createSystem( code, k );
		gaus.createSystemDrivers( gearChanger.getDrivingElementsForGear() );
		gaus.solve();
		if ( gaus.getSolution().size() == 0 )
		{
			return false;
		}
		float calculatedI = gaus.getSolution()[code[1].getElem1().getSerialNumber()];
		if ( abs( calculatedI ) > 0.001 && m_iTarget.findIn( 1.0 / calculatedI ) )
		{
			tmpI.push_back( 1.0 / calculatedI );
		}
		else
		{
			return false;
		}

	} while ( gearChanger.next() );
	//сравниваем полученные передаточные отношения с искомыми
	if ( m_iTarget == tmpI )
	{
		m_iReal = tmpI;
		return true;
	}
	else
		return false;
}
