#include "ApplicationBase.h"
#include "Log.h"
#include "Singletons.h"
#include <iostream>

NS_CORE_USING

void ApplicationBase::readWND()
{
	setlocale( LC_ALL, "Russian" );

	size_t w;
	size_t n;
	size_t d;
	NS_CORE Log::log( "\t\t\t�������� ������." );
	NS_CORE Log::log( "����� �������� �������:	", false );
	std::cin >> w;
	NS_CORE Log::log( "���������� ��:		", false );
	std::cin >> n;
	NS_CORE Log::log( "���������� ��������� ����������:	", false );
	std::cin >> d;
	NS_CORE Singletons::getInstance()->setGlobalParameters( w, n, d );
}