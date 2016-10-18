#pragma once

#include <string>
#include "GlobalDefines.h"

NS_CORE_START


class TSettings
{
public:

	struct DefKSettings
	{
		bool				_calcKQuick;
		bool				_doTest;
	};

private:

	static const std::string					s_calcKQuick;
	static const std::string					s_doTest;

	bool										loadSettingsFromFile();
	void										saveSettingsToFile();

	void										generateDefaultSettings();

	DefKSettings								m_defKSettings;

	TSettings();
	TSettings( const TSettings& ) = delete;

public:

	static TSettings*							getInstance();

	const DefKSettings&							getDefKSettings() const;

};

NS_CORE_END