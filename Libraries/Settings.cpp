#include "Settings.h"
#include "Singletons.h"
#include "SettingsItem.h"

NS_CORE_USING


const std::string								Settings::s_doTest = "do_test";
const std::string								Settings::s_calcKQuick = "calc_k_quick";

std::string boolTostr( const bool bVal )
{
	if ( bVal )
		return "yes";
	else
		return "no";
}

bool strToBool( const std::string& str )
{
	return str == "yes";
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

		loadedCount++;
	}

	return loadedCount > 0;
}

void Settings::saveSettingsToFile()
{
	auto fm = Singletons::getInstance()->getIOFileManager();

	fm->writeToFile( IOFileManager::eOutputFileType::SETTINGS, SettingsItem( s_doTest, boolTostr( m_defKSettings._doTest ) ) );
	fm->writeToFile( IOFileManager::eOutputFileType::SETTINGS, SettingsItem( s_calcKQuick, boolTostr( m_defKSettings._calcKQuick ) ) );
}

void Settings::generateDefaultSettings()
{
	m_defKSettings._calcKQuick = true;
	m_defKSettings._doTest = false;
	saveSettingsToFile();
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
