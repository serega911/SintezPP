#include <algorithm>

#include "Settings.h"
#include "Singletons.h"
#include "SettingsItem.h"
#include "Log.h"

NS_CORE_USING


const std::string								Settings::s_doTest = "do_test";
const std::string								Settings::s_calcKQuick = "calc_k_quick";
const std::string								Settings::s_twoFrictions = "use2frict";
const std::string								Settings::s_twoBrakes = "use2brakes";
const std::string								Settings::s_testStep = "test_step";
const std::string								Settings::s_kStep = "k_step";

std::string boolTostr( const bool bVal )
{
	if ( bVal )
		return "yes";
	else
		return "no";
}

bool strToBool( const std::string& str )
{
	bool ret = str == "yes";
	return ret;
}

int strToInt( const std::string& str )
{
	int ret = std::stoi(str);
	return ret;
}

double strTodouble( const std::string& str )
{
	std::string tmp = str;
	std::replace(tmp.begin(), tmp.end(), '.', ',');
	double ret = std::stof(tmp);
	return ret;
}

std::string intToStr( const int iVal )
{
	std::string ret = std::to_string( iVal );
	return ret;
}

std::string doubleToStr( const double fVal )
{
	std::string ret = std::to_string(fVal);
	return ret;
}

bool Settings::loadSettingsFromFile()
{
	auto fm = Singletons::getInstance()->getIOFileManager();
	SettingsItem item;
	size_t loadedCount = 0;

	while ( fm->loadFromFile( IOFileManager::eOutputFileType::SETTINGS, item ) )
	{
		const auto& key = item.getKey();
		const auto& val = item.getValue();

		if ( s_doTest == key )
		{
			m_defKSettings._doTest = strToBool( val );
		}
		else if ( s_calcKQuick == key )
		{
			m_defKSettings._calcKQuick = strToBool( val );
		}
		else if ( s_twoFrictions == key )
		{
			m_generalSettings._gearChangerUseTwoFrictions = strToBool( val );
		}
		else if ( s_twoBrakes == key )
		{
			m_generalSettings._gearChangerUseTwoBrakes = strToBool( val );
		}
		else if ( s_testStep == key )
		{
			m_defKSettings._testStep = strTodouble( val );
		}
		else if (s_kStep == key)
		{
			m_defKSettings._kStep = strTodouble(val);
		}
		loadedCount++;
	}

	return loadedCount > 0;
}

void Settings::saveSettingsToFile()
{
	auto fm = Singletons::getInstance()->getIOFileManager();

	fm->writeToFile( IOFileManager::eOutputFileType::SETTINGS, SettingsItem( s_doTest, boolTostr( m_defKSettings._doTest ) ) );
	fm->writeToFile( IOFileManager::eOutputFileType::SETTINGS, SettingsItem( s_testStep, doubleToStr( m_defKSettings._testStep ) ) );
	fm->writeToFile( IOFileManager::eOutputFileType::SETTINGS, SettingsItem( s_kStep, doubleToStr(m_defKSettings._kStep)));
	fm->writeToFile( IOFileManager::eOutputFileType::SETTINGS, SettingsItem( s_calcKQuick, boolTostr( m_defKSettings._calcKQuick ) ) );

	fm->writeToFile( IOFileManager::eOutputFileType::SETTINGS, SettingsItem( s_twoFrictions, boolTostr( m_generalSettings._gearChangerUseTwoFrictions ) ) );
	fm->writeToFile( IOFileManager::eOutputFileType::SETTINGS, SettingsItem( s_twoBrakes, boolTostr( m_generalSettings._gearChangerUseTwoBrakes ) ) );
}

void Settings::generateDefaultSettings()
{
	m_defKSettings._calcKQuick = true;
	m_defKSettings._doTest = false;
	m_defKSettings._testStep = 0.5;
	m_defKSettings._kStep = 0.1;

	m_generalSettings._gearChangerUseTwoFrictions = true;
	m_generalSettings._gearChangerUseTwoBrakes = false;

	saveSettingsToFile();

	Log::log( "Default settings file was created. Please, check it and run application again." );
	NS_CORE Log::pause();
	exit( 0 );
}

core::Settings::Settings()
{
	if ( !loadSettingsFromFile() )
		generateDefaultSettings();
}

Settings* Settings::getInstance()
{
	static Settings settings;
	return &settings;
}

const Settings::DefKSettings& Settings::getDefKSettings() const
{
	return m_defKSettings;
}

const Settings::GeneralSettings& Settings::getGeneralSettings() const
{
	return m_generalSettings;
}
