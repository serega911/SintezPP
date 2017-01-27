#include "ApplicationBase.h"
#include "Log.h"
#include "Singletons.h"
#include <iostream>

NS_CORE_USING

void ApplicationBase::readUIGeneralData()
{
	setlocale( LC_ALL, "Russian" );

	size_t w;
	size_t n;
	size_t d;
	NS_CORE Log::log( "\t\t\tИсходные данные." );
	NS_CORE Log::log( "Число степеней свободы:	", false );
	std::cin >> w;
	NS_CORE Log::log( "Количество ПМ:		", false );
	std::cin >> n;
	NS_CORE Log::log( "Количество элементов управления:	", false );
	std::cin >> d;
	NS_CORE Singletons::getInstance()->setGlobalParameters( w, n, d );
}

void core::ApplicationBase::readUISpecialData()
{
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
		NS_CORE Singletons::getInstance()->addRangeK( NS_CORE Range( NS_CORE InternalGearRatioValue( beg ), NS_CORE InternalGearRatioValue( end ) ) );
	}

	const size_t numberOfGears = NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears;
	NS_CORE Log::log( "Количество передач:	" + std::to_string( numberOfGears ) );

	NS_CORE Log::log( "Передаточные отношения : ", false );
	for ( size_t i = 0; i < numberOfGears; i++ )
	{
		double ratio = 0;
		std::cin >> ratio;
		if ( ratio != 0 )
			NS_CORE Singletons::getInstance()->addGearRatio( ratio );
		else
		{
			for ( size_t j = i; j < numberOfGears; j++ )
				NS_CORE Singletons::getInstance()->addGearRatio( 0 );
			break;
		}
	}

	//NS_CORE Singletons::getInstance()->getIOFileManager()->writeSolutionData();
}

void core::ApplicationBase::setUISpecialData( const UISpecialData& data )
{
	for ( int i = 0; i < data._ranges.size(); i++ )
		NS_CORE Singletons::getInstance()->addRangeK( NS_CORE Range( NS_CORE InternalGearRatioValue( data._ranges[i].first ), NS_CORE InternalGearRatioValue( data._ranges[i].second ) ) );

	const size_t numberOfGears = NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears;
	size_t i = 0;
	for ( i = 0; i < data._i.size(); i++ )
		NS_CORE Singletons::getInstance()->addGearRatio( data._i[i] );
	for ( size_t j = i; j < numberOfGears; j++ )
		NS_CORE Singletons::getInstance()->addGearRatio( 0 );
}

void core::ApplicationBase::showParams()
{
	auto generalData = NS_CORE Singletons::getInstance()->getGeneralData();
	auto initialData = NS_CORE Singletons::getInstance()->getInitialData();

	NS_CORE Log::log( "Количество степеней свободы:	" + std::to_string( initialData._w ) );
	NS_CORE Log::log( "Количество ПМ:	" + std::to_string( initialData._numberOfPlanetaryGears ) );
	
	NS_CORE Log::log( "Количество связей:	" + std::to_string( generalData._numberOfLinks ) );
	NS_CORE Log::log( "Количество фрикционов:	" + std::to_string( generalData._numberOfFrictions ) );
	NS_CORE Log::log( "Количество тормозов:	" + std::to_string( generalData._numberOfBrakes ) );

	for ( int i = 0; i < initialData._ranges.size(); i++ )
		NS_CORE Log::log( "range: [" + std::to_string( initialData._ranges[i].getBegin().getValue() ) + " .. " + std::to_string( initialData._ranges[i].getEnd().getValue() ) + "]" );

	for ( int i = 0; i < initialData._i.size(); i++ )
		NS_CORE Log::log( "i" + std::to_string( i ) + "=" + std::to_string( initialData._i[i].getValue() ) );
}

void core::ApplicationBase::setUIGeneralData( const UIGeneralData& data )
{
	NS_CORE Singletons::getInstance()->setGlobalParameters( data._w, data._n, data._d );
}
