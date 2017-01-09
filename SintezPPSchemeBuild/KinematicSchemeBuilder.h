#pragma once

#include "IScheme.h"
#include"../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/KinematicSchemeData.h"

NS_ARI_START

class KinematicSchemeBuilder
	: public NS_CORE ApplicationBase
{

private:

	void										readUISpecialData();


public:

	void										run() override;

};

NS_ARI_END