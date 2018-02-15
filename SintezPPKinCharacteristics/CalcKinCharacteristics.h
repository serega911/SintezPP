#pragma once

#include <vector>
#include <iostream>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/KinCharacteristicsTypes.h"
#include "../Libraries/GearSetTypes.h"

NS_ARI_START

class CalcKinCharacteristics
	: public NS_CORE ApplicationBase
{
private:

	enum class eQualityCriteria
	{
		K1,
		K2,
		K3,
		K4,
		K5_1,
		K5_2,
		K6,
		K7,
		K8,
		K9,
		K_INTEGRAL
	};

	static std::string qualityCriteriaToString(const eQualityCriteria qc)
	{
		switch (qc)
		{
		case eQualityCriteria::K1:			return "K1";
		case eQualityCriteria::K2:			return "K2";
		case eQualityCriteria::K3:			return "K3";
		case eQualityCriteria::K4:			return "K4";
		case eQualityCriteria::K5_1:		return "K5_1";
		case eQualityCriteria::K5_2:		return "K5_2";
		case eQualityCriteria::K6:			return "K6";
		case eQualityCriteria::K7:			return "K7";
		case eQualityCriteria::K8:			return "K8";
		case eQualityCriteria::K9:			return "K9";
		case eQualityCriteria::K_INTEGRAL:	return "K_INT";
		default:							return "UNKNOWN";
			break;
		}
	}

	struct Characteristics: public NS_CORE IIOItem
	{
		NS_CORE Z							_tooth;
		std::vector<NS_CORE W>				_angVelocity;
		std::vector<NS_CORE M>				_torque;
		std::vector<NS_CORE N>				_power;
		std::vector<NS_CORE KpdZac>			_kpdZacStepen;
		std::vector<NS_CORE M>				_kpdTorque;
		std::map<eQualityCriteria, double>	_qualityCriterias;


		template <class T>
		void printCharacteristicsLine( std::map<NS_CORE Element, T> map, std::ostream & stream = std::cout ) const
		{
			for ( const auto& elem : map )
			{
				if ( elem.first != NS_CORE Element::EMPTY )
				{
					if ( &std::cout == &stream )
						elem.first.print( NS_CORE eColor::GREEN );
					else
						elem.first.print( stream );
					stream << "      ";
				}
			}
			stream << std::endl;
			for ( const auto& elem : map )
			{
				if ( elem.first != NS_CORE Element::EMPTY )
				{
					stream.width( 7 );
					stream.precision( 4 );
					stream << std::left << elem.second << " ";
				}
			}
			stream << std::endl;
		}

		template <class T>
		void printCharacteristicsLine(std::map<eQualityCriteria, T> map, std::ostream & stream = std::cout) const
		{
			for (const auto& elem : map)
			{
				stream.width(7);
				stream.precision(4);
				stream << qualityCriteriaToString(elem.first);
			}
			stream << std::endl;
			for (const auto& elem : map)
			{
				stream.width(7);
				stream.precision(4);
				stream << std::left << elem.second << " ";
			}
			stream << std::endl;
		}

		virtual void						writeToFile( std::ostream& stream ) const
		{
			stream << "Z:" << std::endl;
			printCharacteristicsLine( _tooth, stream );

			stream << "M:" << std::endl;
			for ( const auto& z : _torque )
				printCharacteristicsLine( z, stream );

			stream << "W:" << std::endl;
			for ( const auto& z : _angVelocity )
				printCharacteristicsLine( z, stream );

			stream << "N:" << std::endl;
			for ( const auto& z : _power )
				printCharacteristicsLine( z, stream );

			stream << "M_KPD:" << std::endl;
			for ( const auto& z : _kpdTorque )
				printCharacteristicsLine( z, stream );

			stream << "QK:" << std::endl;
			printCharacteristicsLine(_qualityCriterias, stream);
		}

		virtual bool						loadFromFile( std::istream& )
		{
			return false;
		};
	};

	static const double							s_inTorque;
	static const NS_CORE RatioValue				s_inVelocity;
	std::vector<Characteristics>				m_characteristics;

	void										printCharacteristics( const NS_CORE Code code, const Characteristics& ch );


	NS_CORE Z									calcZ(const NS_CORE InternalGearRatios& intRatios, const NS_CORE GearSetTypes& types);
	NS_CORE Z									calcZHelper(const NS_CORE InternalGearRatioValue& intRatio, const NS_CORE GearSetNumber& gearSetN, const NS_CORE eGearSetType& type);

	std::vector<NS_CORE M>						calcM( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios );
	std::vector<NS_CORE W>						calcW(const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios, const NS_CORE Z& tooth);
	std::vector<NS_CORE N>						calcN( const std::vector<NS_CORE W>& w, const std::vector<NS_CORE M>& m );
	std::vector<NS_CORE KpdZac>					calcKpdZacStepen( const NS_CORE InternalGearRatios& intRatios, const std::vector<NS_CORE W>& w, const std::vector<NS_CORE N>& n );
	std::vector<NS_CORE M>						calcMh( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios, std::vector<NS_CORE KpdZac> kpdZacStepen );
	std::map<eQualityCriteria, double>			calcQualityCriterias( const std::vector<NS_CORE M> & mKpd, std::vector<NS_CORE W> angVel );


public:

	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END