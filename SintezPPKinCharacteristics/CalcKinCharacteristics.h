#pragma once

#include <vector>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"


NS_ARI_START

class CalcKinCharacteristics
	: public NS_CORE ApplicationBase
{
private:

	typedef std::map<NS_CORE eMainElement, int>	Z;
	typedef std::map<NS_CORE Element, double>	M;
	
	struct Characteristics
	{
		std::vector<Z>	_tooth;
	};

	
	std::vector<Characteristics>				m_characteristics;

	std::vector<Z>								calcZ( const NS_CORE InternalGearRatios& intRatios );
	Z											calcZHelper( const NS_CORE InternalGearRatioValue& intRatio );

	M											calcM( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios );

public:

	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END