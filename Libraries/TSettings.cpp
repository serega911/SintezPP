#include "TSettings.h"
#include "TSingletons.h"
#include "TSettingsItem.h"

NS_CORE_USING


const std::string								TSettings::s_doTest = "do_test";
const std::string								TSettings::s_calcKQuick = "calc_k_quick";

const char* boolTostr( const bool bVal )
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

bool TSettings::loadSettingsFromFile()
{
	auto fm = TSingletons::getInstance()->getIOFileManager();
	TSettingsItem item;
	size_t loadedCount = 0;

	while ( fm->loadFromFile( TIOFileManager::eOutputFileType::SETTINGS, item ) )
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

void TSettings::saveSettingsToFile()
{
	auto fm = TSingletons::getInstance()->getIOFileManager();

	fm->writeToFile( TIOFileManager::eOutputFileType::SETTINGS, TSettingsItem( s_doTest, boolTostr( m_defKSettings._doTest ) ) );
	fm->writeToFile( TIOFileManager::eOutputFileType::SETTINGS, TSettingsItem( s_calcKQuick, boolTostr( m_defKSettings._calcKQuick ) ) );
}

void TSettings::generateDefaultSettings()
{
	m_defKSettings._calcKQuick = true;
	m_defKSettings._doTest = false;
	saveSettingsToFile();
}

core::TSettings::TSettings()
{
	if ( !loadSettingsFromFile() )
		generateDefaultSettings();
}

TSettings* TSettings::getInstance()
{
	static TSettings settings;
	return &settings;
}

const TSettings::DefKSettings& TSettings::getDefKSettings() const
{
	return m_defKSettings;
}
