#include "TSingletons.h"
#include <iostream>


pss::TSingletons::TSingletons()
{
}

void pss::TSingletons::calculateNumbersOfElements()
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
			if ( m_initialData._numberOfPlanetaryGears == 1 )
				  {
					  std::cout << "Ошибка: Один планетарный ряд при трех степенях свободы!\n";
					  system( "pause" );
					  return;
				  }
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
				   std::cout << "Ошибка: Некорректное количество степеней свободы!\n";
				   system( "pause" );
				   return;
		}
			break;
			
		}
		m_generalData._numberOfActuatedDrivingElements = m_initialData._w - 1;
	}
}

pss::TSingletons* pss::TSingletons::getInstance()
{
	static pss::TSingletons Singletons;
	return &Singletons;
}

pss::TSingletons::~TSingletons()
{
}

pss::TIOFileManager* pss::TSingletons::getIOFileManager()
{
	return pss::TIOFileManager::getInstance();
}

const pss::GeneralData& pss::TSingletons::getGeneralData() const
{
	return m_generalData;
}

const pss::InitialData& pss::TSingletons::getInitialData() const
{
	return m_initialData;
}

void pss::TSingletons::setGlobalParameters( int w, int n )
{
	m_initialData._w = w;
	m_initialData._numberOfPlanetaryGears = n;
	calculateNumbersOfElements();
	getIOFileManager()->writeSolutionData();
}

void pss::TSingletons::addRangeK( const TRange& range )
{
	m_initialData._ranges.push_back( range );
}

void pss::TSingletons::addGearRatio( const float& i )
{
	m_initialData._i.push_back( i );
}
