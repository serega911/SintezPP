#include <iostream>

#include "../Libraries/Log.h"
#include "../Libraries/Range.h"
#include "../Libraries/Singletons.h"

#include "AppManager.h"
#include "Command.h"


NS_ARI_USING

//const std::string prefix =  "..\\Debug\\";
const std::string prefix =  "";

ari::AppManager::AppManager( const Data& data )
: AppManagerBase( data ), m_isDataFilled( false )
{
}

bool ari::AppManager::start()
{
	while ( true )
	{
		system( "cls" );
		NS_CORE Log::log( "1. Генерация" );
		NS_CORE Log::log( "2. Определение К" );
		NS_CORE Log::log( "3. Прорисовка" );
		NS_CORE Log::log( "4. Назад" );

		int ans;
		std::cin >> ans;

		switch ( ans )
		{
		case 1: startGenerate();	break;
		case 2: startDefK();		break;
		case 3: startSchemeBuild();	break;
		case 4: return true;		break;
		}
	}
	
	return true;
}

ari::Data ari::AppManager::readGeneral()
{
	setlocale( LC_ALL, "Russian" );

	NS_ARI Data ret;

	NS_CORE Log::log( "\t\t\tИсходные данные." );
	NS_CORE Log::log( "Число степеней свободы:	", false );
	std::cin >> ret._w;
	NS_CORE Log::log( "Количество ПМ:		", false );
	std::cin >> ret._n;
	NS_CORE Log::log( "Количество элементов управления:	", false );
	std::cin >> ret._d;

	NS_CORE Singletons::getInstance()->setGlobalParameters( ret._w, ret._n, ret._d );

	return ret;
}

ari::SpecialData ari::AppManager::readSpecial()
{
	NS_ARI SpecialData ret;

	int countIntervals = 0;
	NS_CORE Log::log( "Количество диапазонов : ", false );
	std::cin >> countIntervals;
	for ( int i = 0; i < countIntervals; i++ )
	{
		double beg, end;
		NS_CORE Log::log( "Начало диапазона:	", false );
		std::cin >> beg;
		NS_CORE Log::log( "Конец диапазона:	", false );
		std::cin >> end;
		ret._ranges.emplace_back( std::pair<float, float>( beg, end ) );
		//command.addParam( rangeBeginKey, std::to_string( beg ) );
		//command.addParam( rangeEndKey, std::to_string( end ) );
	}

	const size_t numberOfGears = NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears;
	NS_CORE Log::log( "Количество передач:	" + std::to_string( numberOfGears ) );

	NS_CORE Log::log( "Передаточные отношения : ", false );
	for ( size_t i = 0; i < numberOfGears; i++ )
	{
		double ratio = 0;
		std::cin >> ratio;
		if ( ratio != 0 )
			ret._ratios.push_back( ratio );
		else
		{
			for ( size_t j = i; j < numberOfGears; j++ )
				ret._ratios.push_back( 0 );
			break;
		}
	}

	return ret;
}

void ari::AppManager::startGenerate()
{
	Command command = createCommand( prefix + "SintezPPGenerate.exe", nullptr );
	runApplication( command );
}

void ari::AppManager::startDefK()
{
	fillSpecialData();

	Command command = createCommand( prefix + "SintezPPDefK.exe", &m_speciallData );

	while ( runApplication( command ) )
		startGenerate();
}

void ari::AppManager::startSchemeBuild()
{
	fillSpecialData();

	Command command = createCommand( prefix + "SintezPPSchemeBuild.exe", &m_speciallData );

	while ( runApplication( command ) )
		startDefK();
}

void ari::AppManager::fillSpecialData()
{
	if ( !m_isDataFilled )
	{
		m_speciallData = readSpecial();
		m_isDataFilled = true;
	}
}

int ari::AppManager::runApplication( const Command& command )
{
	return system( command.get().c_str() );
}
