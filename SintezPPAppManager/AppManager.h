#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"

NS_ARI_START

class AppManager : public NS_CORE ApplicationBase
{
private:

	bool										m_isDataFilled;

	void										fillSpecialData();

	NS_CORE UIGeneralData						getGeneralData();
	NS_CORE UISpecialData						getSpecialData();

	void										startGenerate();
	void										startDefK();
	void										startSchemeBuild();
	void										startCalcCharacteristics();

public:

	AppManager();

	virtual void								run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END

