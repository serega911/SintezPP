#include "DefK.h"

#include "DefKNuton.h"
#include "DefKSimple.h"
#include "DefKSelection.h"

#include "../Libraries/TSingletons.h"
#include "../Libraries/TLog.h"

NS_ARI_USING


void DefK::readInitialData()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE TLog::log( "====  ������ ����������� ������� � ����� ��������� �������. ����������� �.  ====" );

	int W;
	int N;
	NS_CORE TLog::log( "\t\t\t�������� ������." );
	NS_CORE TLog::log( "����� �������� �������:	", false );
	std::cin >> W;
	NS_CORE TLog::log( "���������� ��:		", false );
	std::cin >> N;
	NS_CORE TSingletons::getInstance()->setGlobalParameters( W, N );

	int countIntervals = 0;
	NS_CORE TLog::log( "���������� ���������� : ", false );
	std::cin >> countIntervals;
	for ( int i = 0; i < countIntervals; i++ )
	{
		double beg, end;
		NS_CORE TLog::log( "������ ���������:	", false );
		std::cin >> beg;
		NS_CORE TLog::log( "����� ���������:	", false );
		std::cin >> end;
		NS_CORE TSingletons::getInstance()->addRangeK( NS_CORE TRange( NS_CORE TKValue( beg ), NS_CORE TKValue( end ) ) );
	}
	NS_CORE TLog::log( "������������ ���������. ����������� ���������� ���������� - ", false );
	NS_CORE TLog::log( NS_CORE TSingletons::getInstance()->getInitialData()._numberOfGears );
	NS_CORE TLog::log( "���������� �������:	", false );
	int n;
	std::cin >> n;
	NS_CORE TSingletons::getInstance()->setNumberOfGears(n);
	for ( size_t i = 0; i < NS_CORE TSingletons::getInstance()->getInitialData()._numberOfGears; i++ )
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
		DefKSimple solveSimple;
		NS_CORE TKArray ans = solveSimple.calculate( code );

#define  QUICK_SEARCH
#ifndef QUICK_SEARCH 
		if ( ans.size() == 0 )
		{
			DefKSelection solveSelection;
			ans = solveSelection.calculate( code );
		}
#endif

		for ( const auto& it : ans )
		{
			if ( it.check() )
			{
				NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, code );
				NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K, it );
			}
		}
	}
	system( "pause" );
}