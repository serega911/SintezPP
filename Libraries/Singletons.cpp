#include <iostream>

#include "Singletons.h"
#include "Log.h"

NS_CORE_USING

Singletons::Singletons()
{
}

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
	m_generalData._numberOfActuatedDrivingElements = w - 1;
	m_generalData._numberOfLinks = 2 * m_initialData._numberOfPlanetaryGears - m_initialData._w;

	switch ( w )
	{
	case 2:
		{
			m_generalData._numberOfFrictions = 0;	// для двухстепенных блокировочный фрикцион не считаем
			m_generalData._numberOfBrakes = m_initialData._numberOfPlanetaryGears;
			m_initialData._numberOfGears = m_generalData._numberOfBrakes;
		}
		break;
	case 3:
		{
			m_generalData._numberOfFrictions = 2;
			m_generalData._numberOfBrakes = d - m_generalData._numberOfFrictions;

			const auto& settings = getSettings()->getGeneralSettings();
			m_initialData._numberOfGears = m_generalData._numberOfFrictions * m_generalData._numberOfBrakes;
			if ( settings._gearChangerUseTwoFrictions )
				m_initialData._numberOfGears++;
			if ( settings._gearChangerUseTwoBrakes )
				m_initialData._numberOfGears += getCombinatorics()->getSubsetsCount( m_generalData._numberOfBrakes, m_generalData._numberOfActuatedDrivingElements );
		}
		break;
	default:
		{
			Log::warning( true, "Ошибка: Некорректное количество степеней свободы!", Log::CRITICAL, HERE );
		}
		break;
	}

	getIOFileManager()->init();
}

void Singletons::addRangeK( const Range& range )
{
	m_initialData._ranges.push_back( range );
}

void Singletons::addGearRatio( const double& i )
{
	if (i != 0 )
		m_initialData._realNumberOfGears++;
	m_initialData._i.push_back( RatioValue(i) );
}
