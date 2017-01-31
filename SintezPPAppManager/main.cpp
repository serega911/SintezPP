
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Log.h"

#include <vector>
#include <iostream>
#include "TestGenerate.h"
#include "TestDefK.h"
#include "AppManager.h"


#pragma comment(lib, "../Libraries/SintezPPLibary.lib")




void runApplication()
{
	NS_ARI AppManager manager;
	manager.readUIGeneralData();
	manager.run();
}


void executeTests()
{
	std::vector<NS_ARI TestBase*> tests;

	tests.push_back( NS_ARI TestGenerate::create( { 2, 2, 2 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 2, 3, 3 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 2, 3 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 2, 4 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 3, 5 } ) );
	/*
	tests.push_back( NS_ARI TestDefK::create( { 2, 2, 2 } ) );
	tests.push_back( NS_ARI TestDefK::create( { 2, 3, 3 } ) );
	tests.push_back( NS_ARI TestDefK::create( { 3, 2, 3 } ) );
	tests.push_back( NS_ARI TestDefK::create( { 3, 2, 4 } ) );
	tests.push_back( NS_ARI TestDefK::create( { 3, 3, 5 } ) );
	*/



	for ( auto& it : tests )
		it->start();

	for ( auto& it : tests )
		delete it;
}

int main()
{
	setlocale( LC_ALL, "Russian" );

	while ( true )
	{
		system( "cls" );
		NS_CORE Log::log( "1. Модульные тесты" );
		NS_CORE Log::log( "2. Расчет" );
		NS_CORE Log::log( "3. Выход" );

		int ans;
		std::cin >> ans;

		switch ( ans )
		{
		case 1:		executeTests();					break;
		case 2:		runApplication();				break;
		case 3:		exit( 0 );						break;
		}
	}
}