#pragma once

#include <vector>
#include <iostream>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/KinCharacteristicsTypes.h"

NS_ARI_START

class CalcKinCharacteristics
	: public NS_CORE ApplicationBase
{
private:

	struct Characteristics
	{
		std::vector<NS_CORE Z>	_tooth;
		std::vector<NS_CORE W>	_angVelocity;
		std::vector<NS_CORE M>	_torque;
		std::vector<NS_CORE N>	_power;
		std::vector<NS_CORE KpdZac> _kpdZacStepen;
		std::vector<NS_CORE M>	_kpdTorque;
	};

	
	std::vector<Characteristics>				m_characteristics;

	void										printCharacteristics( const NS_CORE Code code, const Characteristics& ch );

	template <class T>
	void printCharacteristicsLine( std::map<NS_CORE Element, T> map )
	{
		for ( const auto& elem : map )
		{
			if ( elem.first != NS_CORE Element::EMPTY )
			{
				elem.first.print(NS_CORE eColor::GREEN);
				std::cout << "      ";
			}
		}
		std::cout << std::endl;
		for ( const auto& elem : map )
		{
			if ( elem.first != NS_CORE Element::EMPTY )
			{
				std::cout.width( 8 );
				std::cout.precision( 5 );
				std::cout << std::left << elem.second;
			}
		}
		std::cout << std::endl;
	}


	std::vector<NS_CORE Z>						calcZ( const NS_CORE InternalGearRatios& intRatios );
	NS_CORE Z									calcZHelper( const NS_CORE InternalGearRatioValue& intRatio, const NS_CORE GearSetNumber& gearSetN );

	std::vector<NS_CORE M>						calcM( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios );
	std::vector<NS_CORE W>						calcW( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios );
	std::vector<NS_CORE N>						calcN( const std::vector<NS_CORE W>& w, const std::vector<NS_CORE M>& m );
	std::vector<NS_CORE KpdZac>					calcKpdZacStepen( const NS_CORE InternalGearRatios& intRatios, const std::vector<NS_CORE W>& w, const std::vector<NS_CORE N>& n );
	std::vector<NS_CORE M>						calcMh( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios, std::vector<NS_CORE KpdZac> kpdZacStepen );
	

public:

	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END