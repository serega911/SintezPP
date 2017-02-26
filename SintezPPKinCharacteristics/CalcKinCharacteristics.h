#pragma once

#include <vector>
#include <iostream>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"


NS_ARI_START

class CalcKinCharacteristics
	: public NS_CORE ApplicationBase
{
private:

	typedef std::map<NS_CORE Element, int>		Z;
	typedef std::map<NS_CORE Element, double>	M;
	typedef std::map<NS_CORE Element, double>	W;
	typedef std::map<NS_CORE Element, char>		N;
	
	struct Characteristics
	{
		std::vector<Z>	_tooth;
		std::vector<W>	_angVelocity;
		std::vector<M>	_torque;
		std::vector<N>	_power;
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
				elem.first.print();
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


	std::vector<Z>								calcZ( const NS_CORE InternalGearRatios& intRatios );
	Z											calcZHelper( const NS_CORE InternalGearRatioValue& intRatio, const NS_CORE GearSetNumber& gearSetN );

	std::vector<M>								calcM( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios );
	std::vector<W>								calcW( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios );
	std::vector<N>								calcN( const std::vector<W>& w, const std::vector<M>& m );
			
public:

	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END