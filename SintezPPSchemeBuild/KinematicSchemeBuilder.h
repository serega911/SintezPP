#pragma once

#include "IScheme.h"
#include"../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/KinematicSchemeData.h"

NS_ARI_START

class KinematicSchemeBuilder
	: public NS_CORE ApplicationBase
{

public:

	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END