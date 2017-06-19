#include <iostream>

#include "../Libraries/Log.h"
#include "../Libraries/Range.h"
#include "../Libraries/Singletons.h"

#include "AppManager.h"
#include "StartAppCommand.h"
#include "StartAppCommandFactory.h"


NS_ARI_USING

const std::string prefix = "";

void ari::AppManager::run()
{
	while ( true )
	{
		system( "cls" );
		NS_CORE Log::log( "1. Генерация" );
		NS_CORE Log::log( "2. Определение К" );
		NS_CORE Log::log( "3. Прорисовка" );
		NS_CORE Log::log( "4. Определение характеристик" );
		NS_CORE Log::log( "5. Назад" );

		int ans;
		std::cin >> ans;

		switch ( ans )
		{
		case 1: startGenerate();			break;
		case 2: startDefK();				break;
		case 3: startSchemeBuild();			break;
		case 4: startCalcCharacteristics();	break;
		case 5: return;						break;
		}
	}

}

void ari::AppManager::startGenerate()
{
	StartAppCommand_p command = StartAppCommandFactory::create( prefix + "SintezPPGenerate.exe", getGeneralData() );
	command->execute();
}

void ari::AppManager::startDefK()
{
	fillSpecialData();

	StartAppCommand_p command = StartAppCommandFactory::create( prefix + "SintezPPDefK.exe", getGeneralData(), getSpecialData() );

	while ( command->execute() )
		startGenerate();
}

void ari::AppManager::startSchemeBuild()
{
	fillSpecialData();

	StartAppCommand_p command = StartAppCommandFactory::create( prefix + "SintezPPSchemeBuild.exe", getGeneralData(), getSpecialData() );

	while ( command->execute() )
		startDefK();
}


void ari::AppManager::startCalcCharacteristics()
{
	fillSpecialData();

	StartAppCommand_p command = StartAppCommandFactory::create( prefix + "SintezPPKinCharacteristics.exe", getGeneralData(), getSpecialData() );

	while ( command->execute() )
		startSchemeBuild();
}


void ari::AppManager::fillSpecialData()
{
	if ( !m_isDataFilled )
	{
		readUISpecialData();
		m_isDataFilled = true;
	}
}

bool ari::AppManager::checkRequirements() const
{
	return true;
}

NS_CORE UIGeneralData ari::AppManager::getGeneralData()
{
	const auto& singInitialData = NS_CORE Singletons::getInstance()->getInitialData();
	const auto& singGeneralData = NS_CORE Singletons::getInstance()->getGeneralData();

	NS_CORE UIGeneralData generalData;

	generalData._w = singInitialData._w;
	generalData._n = singInitialData._numberOfPlanetaryGears;
	generalData._d = singGeneralData._numberOfBrakes + singGeneralData._numberOfFrictions;

	return generalData;
}

NS_CORE UISpecialData ari::AppManager::getSpecialData()
{
	const auto& singInitialData = NS_CORE Singletons::getInstance()->getInitialData();
	const auto& singGeneralData = NS_CORE Singletons::getInstance()->getGeneralData();

	NS_CORE UISpecialData specialData;

	const int iSize = singInitialData._i.size();
	specialData._i.resize( iSize );
	for ( int i = 0; i < iSize; i++ )
		specialData._i.emplace_back( singInitialData._i[i].getValue() );

	const int rangesSize = singInitialData._ranges.size();
	specialData._ranges.resize( rangesSize );
	for ( int i = 0; i < rangesSize; i++ )
	{
		specialData._ranges[i].first = singInitialData._ranges[i].getBegin().getValue();
		specialData._ranges[i].second = singInitialData._ranges[i].getEnd().getValue();
	}

	return specialData;
}

ari::AppManager::AppManager()
	: m_isDataFilled( false )
{

}
