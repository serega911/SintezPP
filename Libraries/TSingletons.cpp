#include <iostream>

#include "TSingletons.h"
#include "TLog.h"

NS_CORE_USING

TSingletons::TSingletons()
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
// 			m_generalData._numberOfFrictions = 0;	// ��� ������������� ������������� �������� �� �������
// 			m_generalData._numberOfLinks = 2 * m_initialData._numberOfPlanetaryGears - m_initialData._w;
// 			m_initialData._numberOfGears = m_generalData._numberOfBrakes;
// 		}
// 			break;
// 		case 3:
// 		{
// 			TLog::warning( m_initialData._numberOfPlanetaryGears == 1, "������: ���� ����������� ��� ��� ���� �������� �������!", TLog::CRITICAL, "TSingletons::calculateNumbersOfElements()" );
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
// 			TLog::warning( true, "������: ������������ ���������� �������� �������!", TLog::CRITICAL, "TSingletons::calculateNumbersOfElements()" );
// 		}
// 			break;
// 			
// 		}
// 		m_generalData._numberOfActuatedDrivingElements = m_initialData._w - 1;
// 	}
// }

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

TLoaderFromFile* TSingletons::getLoaderFromFile()
{
	return TLoaderFromFile::getInstance();
}

TCombinatorics* TSingletons::getCombinatorics()
{
	return TCombinatorics::getInstance();
}

const GeneralData& TSingletons::getGeneralData() const
{
	return m_generalData;
}

const InitialData& TSingletons::getInitialData() const
{
	return m_initialData;
}

void TSingletons::setGlobalParameters( const size_t w, const size_t n, const size_t d )
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

	getIOFileManager()->writeSolutionData();
}

void TSingletons::setNumberOfGears( const size_t n )
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
		TLog::warning( true, "W = 2. Can\'t set number of gears", TLog::NON_CRITICAL, "TSingletons::setNumberOfGears" );
	}
}

void TSingletons::addRangeK( const TRange& range )
{
	m_initialData._ranges.push_back( range );
}

void TSingletons::addGearRatio( const double& i )
{
	m_initialData._i.push_back( TIValue(i) );
}
