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
	double										m_a;
	double										m_b;
	double										m_c;
	double										m_kpdSum;

	Function() = delete;
	Function( const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );

	static Function_p							createAD( const NS_CORE InternalGearRatioValue& k, const NS_CORE W& w, const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );
	static Function_p							createBE( const NS_CORE InternalGearRatioValue& k, const NS_CORE W& w, const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );
	static Function_p							createCF( const NS_CORE InternalGearRatioValue& k, const NS_CORE W& w, const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );

public:

	static int									sign( char c );
	static Function_p							create( const NS_CORE InternalGearRatioValue& k, const NS_CORE W& w, const NS_CORE N& n, const NS_CORE GearSetNumber gearSet );
	virtual double								calc(double) const override;

};

NS_ARI_END