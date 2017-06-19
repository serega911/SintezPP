#pragma once

#include<memory>

#include "../Libraries/MappedSystem.h"
#include "../Libraries/InternalGearRatioValue.h"
#include "IFunction.h"
#include "../Libraries/KinCharacteristicsTypes.h"

NS_ARI_START

class Function;

typedef std::shared_ptr<Function> Function_p;

class Function : public IFunction
{
private:

	int											m_na;
	int											m_nb;
	int											m_nh;
	float										m_a;
	float										m_b;
	float										m_c;
	float										m_kpdSum;

	Function() = delete;
	Function( const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );

	static Function_p							createAD( const NS_CORE InternalGearRatioValue& k, const NS_CORE W& w, const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );
	static Function_p							createBE( const NS_CORE InternalGearRatioValue& k, const NS_CORE W& w, const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );
	static Function_p							createCF( const NS_CORE InternalGearRatioValue& k, const NS_CORE W& w, const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );

public:

	static int									sign( char c );
	static Function_p							create( const NS_CORE InternalGearRatioValue& k, const NS_CORE W& w, const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );
	virtual float								calc( float ) const override;

};

NS_ARI_END