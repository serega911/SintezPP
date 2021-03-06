#pragma once

#include <string>
#include "GlobalDefines.h"

NS_CORE_START


class Settings
{
public:

	struct DefKSettings
	{
		bool				_calcKQuick;
		bool				_doTest;
		double				_testStep;
		double				_kStep;
	};

	struct GeneralSettings
	{
		bool				_gearChangerUseTwoFrictions;
		bool				_gearChangerUseTwoBrakes;
	};

private:

	static const std::string					s_calcKQuick;
	static const std::string					s_doTest;
	static const std::string					s_twoFrictions;
	static const std::string					s_twoBrakes;
	static const std::string					s_testStep;
	static const std::string					s_kStep;

	bool										loadSettingsFromFile();
	void										saveSettingsToFile();

	void										generateDefaultSettings();

	DefKSettings								m_defKSettings;
	GeneralSettings								m_generalSettings;

	Settings();
	Settings( const Settings& ) = delete;

public:

	static Settings*							getInstance();

	const DefKSettings&							getDefKSettings() const;
	const GeneralSettings&						getGeneralSettings() const;

};

NS_CORE_END