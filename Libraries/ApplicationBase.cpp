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
	NS_CORE Log::askForValue("Число степеней свободы:", w);
	NS_CORE Log::askForValue("Количество ПМ:", n);
	NS_CORE Log::askForValue("Количество элементов управления:", d);
	
	NS_CORE Singletons::getInstance()->setGlobalParameters( w, n, d );
}

void core::ApplicationBase::readUISpecialData()
{
	int countIntervals = 0;
	NS_CORE Log::askForValue( "Количество диапазонов:", countIntervals );

	for ( int i = 0; i < countIntervals; i++ )
	{
 		double beg, end;
		NS_CORE Log::askFor2Value("Диапазон # " + std::to_string(i+1), "Начало:", "Конец:", beg, end);
		NS_CORE Singletons::getInstance()->addRangeK( NS_CORE Range( NS_CORE InternalGearRatioValue( beg ), NS_CORE InternalGearRatioValue( end ) ) );
	}

	const size_t numberOfGears = NS_CORE Singletons::getInstance()->getInitialData()._numberOfGears;
	NS_CORE Log::showValue( "Количество передач:", numberOfGears );

	NS_CORE Log::log( "Передаточные отношения: " );
	for ( size_t i = 0; i < numberOfGears; i++ )
	{
		double ratio = 0;
		NS_CORE Log::askForValue( std::to_string(i+1) + " передача:", ratio );
		if ( ratio != 0 )
			NS_CORE Singletons::getInstance()->addGearRatio( ratio );
		else
		{
			for ( size_t j = i; j < numberOfGears; j++ )
				NS_CORE Singletons::getInstance()->addGearRatio( 0 );
			break;
		}
	}
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

	NS_CORE Log::log( "Параметры расчета:", true, NS_CORE eColor::GREEN );

	NS_CORE Log::showValue( "Количество степеней свободы:", initialData._w );
	NS_CORE Log::showValue( "Количество ПМ:", initialData._numberOfPlanetaryGears );
	
	NS_CORE Log::showValue( "Количество связей:", generalData._numberOfLinks );
	NS_CORE Log::showValue( "Количество фрикционов:", generalData._numberOfFrictions );
	NS_CORE Log::showValue( "Количество тормозов:", generalData._numberOfBrakes );

	for ( int i = 0; i < initialData._ranges.size(); i++ )
		NS_CORE Log::show2Value( "Диапазон #" + std::to_string( i+1 ), " .. ", initialData._ranges[i].getBegin().getValue(), initialData._ranges[i].getEnd().getValue() );

	for ( int i = 0; i < initialData._i.size(); i++ )
		NS_CORE Log::showValue( "i" + std::to_string( i + 1 ) + ":", initialData._i[i].getValue() );
}

void core::ApplicationBase::setUIGeneralData( const UIGeneralData& data )
{
	NS_CORE Singletons::getInstance()->setGlobalParameters( data._w, data._n, data._d );
}
