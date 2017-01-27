#pragma once

#include "../Libraries/GlobalDefines.h"

#include "AppManagerBase.h"

NS_ARI_START

class AppManager : public AppManagerBase
{
private:

	SpecialData									m_speciallData;
	bool										m_isDataFilled;

	void										fillSpecialData();

	void										startGenerate();
	void										startDefK();
	void										startSchemeBuild();

	int											runApplication( const Command& command );

public:

	AppManager( const Data& data );

	virtual bool								start() override;

	static Data									readGeneral();
	static SpecialData							readSpecial();

};

NS_ARI_END

