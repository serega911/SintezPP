#include <iostream>

#include "TSingletons.h"
#include "TLog.h"

NS_CORE_USING

TSingletons::TSingletons()
{
}

void TSingletons::calculateNumbersOfElements()
{
	if ( m_initialData._w != 0 && m_initialData._numberOfPlanetaryGears != 0 )
	{
		switch ( m_initialData._w )
		{
		case 2:
		{
			m_generalData._numberOfBrakes = m_initialData._numberOfPlanetaryGears;
			m_generalData._numberOfFrictions = 0;	// для двухстепенных блокировочный фрикцион не считаем
			m_generalData._numberOfLinks = 2 * m_initialData._numberOfPlanetaryGears - m_initialData._w;
			m_initialData._numberOfGears = m_generalData._numberOfBrakes;
		}
			break;
		case 3:
		{
			TLog::warning( m_initialData._numberOfPlanetaryGears == 1, "Ошибка: Один планетарный ряд при трех степенях свободы!", TLog::CRITICAL, "TSingletons::calculateNumbersOfElements()" );

			m_generalData._numberOfBrakes = m_initialData._numberOfPlanetaryGears - 1;
			m_generalData._numberOfFrictions = 2;
			m_generalData._numberOfLinks = 2 * m_initialData._numberOfPlanetaryGears - m_initialData._w;
			if ( m_initialData._numberOfPlanetaryGears == 2 )
				m_initialData._numberOfGears = 2;
			else if ( m_initialData._numberOfPlanetaryGears == 3 )
				m_initialData._numberOfGears = 5;
			else if ( m_initialData._numberOfPlanetaryGears == 4 )
				m_initialData._numberOfGears = 9;
		}
			break;
		default:
		{
			TLog::warning( true, "Ошибка: Некорректное количество степеней свободы!", TLog::CRITICAL, "TSingletons::calculateNumbersOfElements()" );
		}
			break;
			
		}
		m_generalData._numberOfActuatedDrivingElements = m_initialData._w - 1;
	}
}

TSingletons* TSingletons::getInstance()
{
	static TSingletons Singletons;
	return &Singletons;
}

TSingletons::~TSingletons()
{
}

TIOFileManager* TSingletons::getIOFileManager()
{
	return TIOFileManager::getInstance();
}

const GeneralData& TSingletons::getGeneralData() const
{
	return m_generalData;
}

const InitialData& TSingletons::getInitialData() const
{
	return m_initialData;
}

void TSingletons::setGlobalParameters( int w, int n )
{
	m_initialData._w = w;
	m_initialData._numberOfPlanetaryGears = n;
	calculateNumbersOfElements();
	getIOFileManager()->writeSolutionData();
}

void TSingletons::addRangeK( const TRange& range )
{
	m_initialData._ranges.push_back( range );
}

void TSingletons::addGearRatio( const float& i )
{
	m_initialData._i.push_back( i );
}
