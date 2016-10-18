#include "ApplicationBase.h"
#include "TLog.h"
#include "TSingletons.h"
#include <iostream>

NS_CORE_USING

void ApplicationBase::readWND()
{
	setlocale( LC_ALL, "Russian" );

	size_t w;
	size_t n;
	size_t d;
	NS_CORE TLog::log( "\t\t\tИсходные данные." );
	NS_CORE TLog::log( "Число степеней свободы:	", false );
	std::cin >> w;
	NS_CORE TLog::log( "Количество ПМ:		", false );
	std::cin >> n;
	NS_CORE TLog::log( "Количество элементов управления:	", false );
	std::cin >> d;
	NS_CORE TSingletons::getInstance()->setGlobalParameters( w, n, d );
}