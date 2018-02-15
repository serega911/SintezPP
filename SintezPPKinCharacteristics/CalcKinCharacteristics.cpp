#include "../Libraries/Singletons.h"
#include "../Libraries/Code.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/MappedSystem.h"
#include "../Libraries/GearSetTypes.h"
#include "../Libraries/GearBoxWithChanger.h"


#include "GearBoxWithChangerSpecialFrictionProcess.h"
#include "CalcKinCharacteristics.h"
#include "Function.h"
#include "SolveFunctionDiv.h"

NS_ARI_USING

const double ari::CalcKinCharacteristics::s_inTorque = 1000;
const NS_CORE RatioValue ari::CalcKinCharacteristics::s_inVelocity = NS_CORE RatioValue(100);

void CalcKinCharacteristics::run()
{
	showParams();

	core::Code code;
	core::InternalGearRatios k;
	core::GearSetTypes	types;
	core::FakeItem	fake;
	std::vector<core::IIOItem*> containers;
	containers.push_back( &code );
	containers.push_back( &k );
	containers.push_back( &types );
	containers.push_back( &fake );

	while ( core::Singletons::getInstance()->getLoaderFromFile()->load( containers, core::IOFileManager::eOutputFileType::KIN_SLOW ) )
	{
		Characteristics ch;
		ch._tooth = calcZ(k, types);
		ch._torque = calcM( code, k );
		ch._angVelocity = calcW( code, k, ch._tooth );
		ch._power = calcN( ch._angVelocity, ch._torque );
		ch._kpdZacStepen = calcKpdZacStepen( k, ch._angVelocity, ch._power );
		ch._kpdTorque = calcMh( code, k, ch._kpdZacStepen );
		ch._qualityCriterias = calcQualityCriterias( ch._kpdTorque, ch._angVelocity );

		printCharacteristics( code, ch );

		NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::RESULT, code );

		NS_CORE GearBoxWithChanger gb( code );
		gb.createChainsForAllgears();
		NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::RESULT, gb );

		NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::RESULT, types );
		NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::RESULT, fake );
		NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::RESULT, k );
		NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::RESULT, ch );
		NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile(NS_CORE IOFileManager::eOutputFileType::RESULT, NS_CORE IOFileManager::end);

		m_characteristics.push_back( ch );
	}
}

bool CalcKinCharacteristics::checkRequirements() const
{
	if ( !NS_CORE Singletons::getInstance()->getIOFileManager()->isFileExists( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW ) )
		return false;

	NS_CORE Ratios i;
	NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::INITIAL_DATA, i );

	//if ( i.size() != NS_CORE Singletons::getInstance()->getInitialData()._i.size() )
	//	return false;

	NS_CORE Range range( NS_CORE InternalGearRatioValue( 0 ), NS_CORE InternalGearRatioValue( 0 ) );
	const auto& ranges = NS_CORE Singletons::getInstance()->getInitialData()._ranges;

	int count = 0;

	while ( NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::INITIAL_DATA, range ) )
	{
		bool finded = false;
		count++;
		for ( const auto& r : ranges )
		{
			if ( r == range )
			{
				finded = true;
				break;
			}
		}

		if ( !finded )
			return false;

	}

	if ( count != ranges.size() )
		return false;

	return true;
}

NS_CORE Z CalcKinCharacteristics::calcZHelper(const NS_CORE InternalGearRatioValue& intRatio, const NS_CORE GearSetNumber& gearSetN, const NS_CORE eGearSetType& type)
{
	NS_CORE Z ret;

	if (intRatio.getValue() < 0 && type == NS_CORE eGearSetType::TYPE_DEFAULT)
	{
		const int Zmin = 14;
		const int Zmax = 100;
		const double M_PI = 3.14159;

		size_t Nsat = size_t(M_PI / asin((intRatio.getAbs() - 1 + (8.0 / Zmin)) / (intRatio.getAbs() + 1)));//округляем в меньшую сторону - отбрасываем дробныю часть
		double Gamma = 14.0f * (intRatio.getAbs() - 1) / Nsat;
		double z1 = 0.123;
		double z2 = 0.123;
		double z4 = 0.123;

		const auto check = [&](double z)
		{
			return (z - (int)z != 0) || (int)z < Zmin;
		};

		for (size_t i = (size_t)Gamma; check(z1) || check(z2) || check(z4); i++)
		{
			z1 = Nsat*i / (intRatio.getAbs() + 1);
			z2 = z1 * intRatio.getAbs();
			z4 = (z2 - z1) / 2;

			if (z1 > Zmax)
				return ret;
		}

		ret[NS_CORE Element(NS_CORE eMainElement::SUN_GEAR, gearSetN)] = (int)z1;
		ret[NS_CORE Element(NS_CORE eMainElement::EPICYCLIC_GEAR, gearSetN)] = (int)z2;
		ret[NS_CORE Element(NS_CORE eMainElement::SATTELITE, gearSetN)] = (int)z4;
	}
	return ret;
}

NS_CORE Z CalcKinCharacteristics::calcZ( const NS_CORE InternalGearRatios& intRatios, const NS_CORE GearSetTypes& types )
{
	NS_CORE Z ret;
	const int n = intRatios.size();

	for (NS_CORE GearSetNumber set(1); set <= NS_CORE GearSetNumber(n); set++){
		NS_CORE Z local = calcZHelper(intRatios[set.getValue() - 1], set, types.get(set));

		if (local.size() != 3)
		{
			ret.clear();
			break;
		}
		else
		{
			ret.insert(local.begin(), local.end());
		}
	}

	return ret;
}

std::vector<NS_CORE M> ari::CalcKinCharacteristics::calcM( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios )
{
	std::vector<NS_CORE M> ret;

	GearBoxWithChangerSpecialFrictionProcess gb( code );
	gb.createChains();

	do
	{
		NS_CORE MappedSystem_p systemM = NS_CORE MappedSystem::createM( gb.getChainsForCurrentGear(), intRatios, s_inTorque );
		NS_CORE Gaus::solve( systemM );

		ret.push_back( systemM->getSolution() );

	} while ( gb.turnOnNextGear() );


	return ret;
}


std::vector<NS_CORE KpdZac> CalcKinCharacteristics::calcKpdZacStepen( const NS_CORE InternalGearRatios& intRatios, const std::vector<NS_CORE W>& w, const std::vector<NS_CORE N>& n )
{
	std::vector<NS_CORE KpdZac> ret;

	NS_CORE Log::warning( w.size() != n.size(), "Wrong size", NS_CORE Log::eWarningImportance::CRITICAL, HERE );

	const int size = w.size();
	const int planetaryGearsCount = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	ret.resize( size );

	for ( int i = 0; i < size; i++ )
	{
		for ( NS_CORE GearSetNumber gearSet( 1 ); gearSet.getValue() <= planetaryGearsCount; ++gearSet )
		{
			NS_CORE Element sun( NS_CORE eMainElement::SUN_GEAR, gearSet );
			NS_CORE Element epy( NS_CORE eMainElement::EPICYCLIC_GEAR, gearSet );
			NS_CORE Element car( NS_CORE eMainElement::CARRIER, gearSet );

			double kpdA = 1;
			double kpdB = 1;
			const double ksi_a_c = 0.02;
			const double ksi_b_c = 0.01;
			const auto k = intRatios[gearSet.getValue() - 1];

			if ( n[i].at( sun ) == '0' && n[i].at( epy ) == '0' && n[i].at( car ) == '0' )
			{
				kpdA = 1;
				kpdB = 1;
			}
			else if ( w[i].at( sun ) && w[i].at( epy ) && w[i].at( car ) )
			{
				NS_CORE Element sun( NS_CORE eMainElement::SUN_GEAR, gearSet );
				NS_CORE Element epy( NS_CORE eMainElement::EPICYCLIC_GEAR, gearSet );

				IFunction_p func = Function::create( k, w[i], n[i], gearSet );
				kpdB = SolveFunctionDiv::create()->calc( func, 0.8f, 1.0f );
				kpdA = 2 * kpdB - 1;
				kpdA = pow( kpdA, -Function::sign( n[i].at( sun ) ) );
				kpdB = pow( kpdB, -Function::sign( n[i].at( epy ) ) );
			}
			else if ( !w[i].at( sun ) && w[i].at( epy ) && w[i].at( car ) )
			{
				double kpdSum = 1 - 1.0f / ( 1 + k.getValue() ) * ( ksi_a_c + ksi_b_c );
				kpdA = 1 / kpdSum;
				kpdB = pow( kpdSum, -Function::sign( n[i].at( epy ) ) );
			}
			else if ( w[i].at( sun ) && !w[i].at( epy ) && w[i].at( car ) )
			{
				double kpdSum = 1 - k.getValue() / ( 1.0f + k.getValue() ) * ( ksi_a_c + ksi_b_c );
				kpdA = pow( kpdSum, -Function::sign( n[i].at( sun ) ) );
				kpdB = 1 / kpdSum;
			}
			else if ( w[i].at( sun ) && w[i].at( epy ) && !w[i].at( car ) )
			{
				kpdA = 1 - ksi_a_c;
				kpdB = 1 - ksi_b_c;
				kpdA = pow( kpdA, -Function::sign( n[i].at( sun ) ) );
				kpdB = pow( kpdB, -Function::sign( n[i].at( epy ) ) );
			}
			else if (!w[i].at(sun) && !w[i].at(epy) && !w[i].at(car))
			{
				//empty gear
				kpdA = 1;
				kpdB = 1;
			}
			else
			{
				NS_CORE Log::warning( true, "Can't calculate KPD", NS_CORE Log::CRITICAL, HERE );
			}

			ret[i][gearSet]._kpdA = kpdA;
			ret[i][gearSet]._kpdB = kpdB;
		}
	}

	return ret;
}

std::vector<NS_CORE M> CalcKinCharacteristics::calcMh( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios, std::vector<NS_CORE KpdZac> kpdZacStepen )
{
	std::vector<NS_CORE M> ret;

	GearBoxWithChangerSpecialFrictionProcess gb( code );
	gb.createChains();

	NS_CORE GearNumber gear( 0 );

	do
	{
		NS_CORE MappedSystem_p systemM = NS_CORE MappedSystem::createMKpd( gb.getChainsForCurrentGear(), intRatios, kpdZacStepen[gear.getValue()], s_inTorque );
		NS_CORE Gaus::solve( systemM );

		ret.push_back( systemM->getSolution() );

		++gear;

	} while ( gb.turnOnNextGear() );


	return ret;
}

std::map<CalcKinCharacteristics::eQualityCriteria, double> ari::CalcKinCharacteristics::calcQualityCriterias( const std::vector<NS_CORE M> & mKpd, std::vector<NS_CORE W> angVel )
{
	std::map<CalcKinCharacteristics::eQualityCriteria, double> ret;

	const double wIn = angVel[0].at( NS_CORE Element::INPUT );
	const double mIn = mKpd[0].at( NS_CORE Element::INPUT );
	const double nIn = mIn * wIn;

	double nMaxForward = 0;
	double nMaxBackward = 0;
	double torqueFrictionMax = 0;
	double torqueBrakeMax = 0;
	double wSatMaxLoaded = 0;
	double wSatMaxUnloaded = 0;
	double wBrakeFrictionMaxUnloaded = 0;
	int gear = 0;


	for ( size_t i = 0; i < mKpd.size(); i++ )
	{
		const double nOut = mKpd[i].at( NS_CORE Element::OUTPUT ) * angVel[i].at( NS_CORE Element::OUTPUT );
		for ( const auto & it : mKpd[i] )
		{
			const auto m = it.second;
			const auto w = angVel[i].at( it.first );
			const auto n = m * w;
			const auto elem = it.first.getElemN();

			if ( elem == NS_CORE eMainElement::FRICTION || elem == NS_CORE eMainElement::BRAKE )
			{
				if ( abs( w ) > abs( wBrakeFrictionMaxUnloaded ) )
					wBrakeFrictionMaxUnloaded = w;

				if ( elem == NS_CORE eMainElement::FRICTION && abs( m ) > abs( torqueFrictionMax ) )
					torqueFrictionMax = m;
				else if ( elem == NS_CORE eMainElement::BRAKE && abs( m ) > abs( torqueBrakeMax ) )
				{
					gear = i;
					torqueBrakeMax = m;
				}
			}

			if ( isCentralElement( it.first.getElemN() ) )
			{
				if ( nOut > 0 && abs( n ) > abs( nMaxForward ) )
					nMaxForward = n;
				else if ( nOut < 0 && abs( n ) > abs( nMaxBackward ) )
					nMaxBackward = n;
			}

			if ( it.first.getElemN() == NS_CORE eMainElement::SATTELITE )
			{
				const double mSun = mKpd[i].at( NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, it.first.getGearSetN() ) );
				const double mEpy = mKpd[i].at( NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, it.first.getGearSetN() ) );
				const double mCar = mKpd[i].at( NS_CORE Element( NS_CORE eMainElement::CARRIER, it.first.getGearSetN() ) );

				const double w = it.second;

				if ( abs( mSun + mEpy + mCar ) < 0.001 )
					if ( abs( w ) > abs( wSatMaxUnloaded ) )
						wSatMaxUnloaded = w;
					else
						if ( abs( w ) > abs( wSatMaxLoaded ) )
							wSatMaxLoaded = w;
			}
		}
	}

	ret[eQualityCriteria::K1] = abs( nMaxForward / nIn );
	ret[eQualityCriteria::K2] = abs( nMaxBackward / nIn );
	ret[eQualityCriteria::K3] = abs( torqueFrictionMax / mIn );
	ret[eQualityCriteria::K4] = abs( torqueBrakeMax / mIn );
	ret[eQualityCriteria::K5_1] = abs( wSatMaxLoaded / wIn );
	ret[eQualityCriteria::K5_2] = abs( wSatMaxUnloaded / wIn );
	ret[eQualityCriteria::K6] = abs( wBrakeFrictionMaxUnloaded / wIn );

	return ret;
}

std::vector<NS_CORE W> CalcKinCharacteristics::calcW(const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios, const NS_CORE Z& tooth)
{
	const auto n = intRatios.size();
	std::vector<NS_CORE W> ret;

	GearBoxWithChangerSpecialFrictionProcess gb( code );
	gb.createChains();

	do
	{
		NS_CORE MappedSystem_p systemW = NS_CORE MappedSystem::createW( gb.getChainsForCurrentGear(), intRatios, s_inVelocity );
		NS_CORE Gaus::solve( systemW );

		auto solution = systemW->getSolution();

		for ( NS_CORE GearSetNumber set( 1 ); set <= NS_CORE GearSetNumber( n ); ++set )
		{
			const auto k = intRatios[set.getValue() - 1].getValue();
			const auto w3 = solution[NS_CORE Element(NS_CORE eMainElement::CARRIER, set)];
			const auto w1 = solution[NS_CORE Element(NS_CORE eMainElement::SUN_GEAR, set)];
			if (k < 0)
				solution[NS_CORE Element(NS_CORE eMainElement::SATTELITE, set)] = 2.0f * (w1 - w3) / (k + 1);
			else
				solution[NS_CORE Element(NS_CORE eMainElement::SATTELITE, set)] = 0;
		}

		ret.push_back( solution );

	} while ( gb.turnOnNextGear() );


	return ret;
}

std::vector<NS_CORE N> CalcKinCharacteristics::calcN( const std::vector<NS_CORE W>& w, const std::vector<NS_CORE M>& m )
{
	std::vector<NS_CORE N> ret;
	NS_CORE Log::warning( w.size() != m.size(), "wrpng size", NS_CORE Log::CRITICAL, HERE );

	const int gearsCount = w.size();

	ret.resize( gearsCount );

	for ( int i = 0; i < gearsCount; i++ )
	{
		for ( auto&it : m[i] )
		{
			const NS_CORE Element elem = it.first;
			const auto torque = it.second;
			const auto angSpeed = w[i].at( elem );

			if ( torque == 0 )
				ret[i][elem] = '0';
			else if ( torque*angSpeed < 0 )
				ret[i][elem] = '-';
			else
				ret[i][elem] = '+';
		}
	}

	return ret;
}



void ari::CalcKinCharacteristics::printCharacteristics( const NS_CORE Code code, const Characteristics& ch )
{
	code.print();

	NS_CORE Log::log( "Z:", true, NS_CORE eColor::AQUA );
	ch.printCharacteristicsLine(ch._tooth);

	NS_CORE Log::log( "M:", true, NS_CORE eColor::AQUA );
	for ( const auto& z : ch._torque )
	{
		ch.printCharacteristicsLine( z );
	}

	NS_CORE Log::log( "W:", true, NS_CORE eColor::AQUA );
	for ( const auto& z : ch._angVelocity )
	{
		ch.printCharacteristicsLine( z );
	}

	NS_CORE Log::log( "N:", true, NS_CORE eColor::AQUA );
	for ( const auto& z : ch._power )
	{
		ch.printCharacteristicsLine( z );
	}

	NS_CORE Log::log( "M_KPD:", true, NS_CORE eColor::AQUA );
	for ( const auto& z : ch._kpdTorque )
	{
		ch.printCharacteristicsLine( z );
	}

	NS_CORE Log::pause();
}
