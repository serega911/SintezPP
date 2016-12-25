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
