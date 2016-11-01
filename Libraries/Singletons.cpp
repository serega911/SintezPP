#include <iostream>

#include "Singletons.h"
#include "Log.h"

NS_CORE_USING

Singletons::Singletons()
{
}

// void TSingletons::calculateNumbersOfElements()
// {
// 	if ( m_initialData._w != 0 && m_initialData._numberOfPlanetaryGears != 0 )
// 	{
// 		switch ( m_initialData._w )
// 		{
// 		case 2:
// 		{
// 			m_generalData._numberOfBrakes = m_initialData._numberOfPlanetaryGears;
// 			m_generalData._numberOfFrictions = 0;	// для двухстепенных блокировочный фрикцион не считаем
// 			m_generalData._numberOfLinks = 2 * m_initialData._numberOfPlanetaryGears - m_initialData._w;
// 			m_initialData._numberOfGears = m_generalData._numberOfBrakes;
// 		}
// 			break;
// 		case 3:
// 		{
// 			TLog::warning( m_initialData._numberOfPlanetaryGears == 1, "Ошибка: Один планетарный ряд при трех степенях свободы!", TLog::CRITICAL, "TSingletons::calculateNumbersOfElements()" );
// 
// 			m_generalData._numberOfBrakes = m_initialData._numberOfPlanetaryGears - 1;
// 			m_generalData._numberOfFrictions = 2;
// 			m_generalData._numberOfLinks = 2 * m_initialData._numberOfPlanetaryGears - m_initialData._w;
// 			if ( m_initialData._numberOfPlanetaryGears == 2 )
// 				m_initialData._numberOfGears = 2;
// 			else if ( m_initialData._numberOfPlanetaryGears == 3 )
// 				m_initialData._numberOfGears = 5;
// 			else if ( m_initialData._numberOfPlanetaryGears == 4 )
// 				m_initialData._numberOfGears = 9;
// 		}
// 			break;
// 		default:
// 		{
// 			TLog::warning( true, "Ошибка: Некорректное количество степеней свободы!", TLog::CRITICAL, "TSingletons::calculateNumbersOfElements()" );
// 		}
// 			break;
// 			
// 		}
// 		m_generalData._numberOfActuatedDrivingElements = m_initialData._w - 1;
// 	}
// }

Singletons* Singletons::getInstance()
{
	static Singletons Singletons;
	return &Singletons;
}

Singletons::~Singletons()
{
}

IOFileManager* Singletons::getIOFileManager()
{
	return IOFileManager::getInstance();
}

LoaderFromFile* Singletons::getLoaderFromFile()
{
	return LoaderFromFile::getInstance();
}

Combinatorics* Singletons::getCombinatorics()
{
	return Combinatorics::getInstance();
}

Settings* core::Singletons::getSettings()
{
	return Settings::getInstance();
}

const GeneralData& Singletons::getGeneralData() const
{
	return m_generalData;
}

const InitialData& Singletons::getInitialData() const
{
	return m_initialData;
}

void Singletons::setGlobalParameters( const size_t w, const size_t n, const size_t d )
{

	m_initialData._w = w;
	m_initialData._numberOfPlanetaryGears = n;

	if (w > 2)
		m_generalData._numberOfFrictions = 2;
	else	
		m_generalData._numberOfFrictions = 0;
	
	m_generalData._numberOfBrakes = d - m_generalData._numberOfFrictions;
	m_generalData._numberOfActuatedDrivingElements = w - 1;

	m_generalData._numberOfLinks = 2 * m_initialData._numberOfPlanetaryGears - m_initialData._w;

	getIOFileManager()->init();
	getIOFileManager()->writeSolutionData();
}

void Singletons::setNumberOfGears( const size_t n )
{
	if ( m_initialData._w > 2 )
	{
		m_initialData._numberOfGears = n;
	}
	else if ( m_initialData._w == 2 && n == m_initialData._numberOfPlanetaryGears )
	{
		m_initialData._numberOfGears = n;
	}
	else
	{
		Log::warning( true, "W = 2. Can\'t set number of gears", Log::NON_CRITICAL, "TSingletons::setNumberOfGears" );
	}
}

void Singletons::addRangeK( const Range& range )
{
	m_initialData._ranges.push_back( range );
}

void Singletons::addGearRatio( const double& i )
{
	m_initialData._i.push_back( RatioValue(i) );
}
