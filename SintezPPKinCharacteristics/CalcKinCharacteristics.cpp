#include "../Libraries/Singletons.h"
#include "../Libraries/Code.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/MappedSystem.h"
#include "../Libraries/GearSetTypes.h"
#include "../Libraries/GearBoxWithChanger.h"


#include "GearBoxWithChangerSpecialFrictionProcess.h"
#include "CalcKinCharacteristics.h"


NS_ARI_USING

void ari::CalcKinCharacteristics::run()
{
	showParams();

	core::Code code;
	core::InternalGearRatios k;
	core::GearSetTypes	types;
	std::vector<core::IIOItem*> containers;
	containers.push_back( &code );
	containers.push_back( &k );
	containers.push_back( &types );

	while ( core::Singletons::getInstance()->getLoaderFromFile()->load( containers, core::IOFileManager::eOutputFileType::KIN_SLOW ) )
	{
		Characteristics ch;
		ch._tooth = calcZ( k );
		ch._torque = calcM( code, k );
		ch._angVelocity = calcW( code, k );
		ch._power = calcN( ch._angVelocity, ch._torque );

		printCharacteristics( code, ch );

		m_characteristics.push_back( ch );
	}
}

bool ari::CalcKinCharacteristics::checkRequirements() const
{
	if ( !NS_CORE Singletons::getInstance()->getIOFileManager()->isFileExists( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW ) )
		return false;

	NS_CORE Ratios i;
	NS_CORE Singletons::getInstance()->getIOFileManager()->loadFromFile( NS_CORE IOFileManager::eOutputFileType::INITIAL_DATA, i );

	if ( i.size() != NS_CORE Singletons::getInstance()->getInitialData()._i.size() )
		return false;

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

ari::CalcKinCharacteristics::Z ari::CalcKinCharacteristics::calcZHelper( const NS_CORE InternalGearRatioValue& intRatio, const NS_CORE GearSetNumber& gearSetN )
{
	const int Zmin = 14;
	const int Zmax = 100;
	const double M_PI = 3.14159;

	Z ret;

	size_t Nsat = M_PI / asin( ( intRatio.getAbs().getValue() - 1 + ( 8.0 / Zmin ) ) / ( intRatio.getAbs().getValue() + 1 ) );//округляем в меньшую сторону - отбрасываем дробныю часть
	double Gamma = 14.0 * ( intRatio.getAbs().getValue() - 1 ) / Nsat;
	double z1 = 0.123;
	double z2 = 0.123;
	double z4 = 0.123;

	const auto check = [&](double z)
	{
		return ( z - (int)z != 0 ) || (int)z < Zmin;
	};

	for ( size_t i = Gamma; check( z1 ) || check( z2 ) || check( z4 ); i++ )
	{
		z1 = Nsat*i / ( intRatio.getAbs().getValue() + 1 );
		z2 = z1 * intRatio.getAbs().getValue();
		z4 = ( z2 - z1 ) / 2;

		if ( z1 > Zmax )
			return ret;
	}
	
	ret[NS_CORE Element(NS_CORE eMainElement::SUN_GEAR, gearSetN)] = z1;
	ret[NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, gearSetN )] = z2;
	ret[NS_CORE Element( NS_CORE eMainElement::SATTELITE, gearSetN )] = z4;

	return ret;
}

std::vector<ari::CalcKinCharacteristics::Z> ari::CalcKinCharacteristics::calcZ( const NS_CORE InternalGearRatios& intRatios )
{
	std::vector<Z> ret;

	for ( size_t i = 0; i < intRatios.size(); i++ ){
		ret.push_back( calcZHelper( intRatios[i], NS_CORE GearSetNumber( i + 1 ) ) );
	}

	for ( size_t i = 0; i < ret.size(); i++ ){
		if ( ret[i].size() != 3 )
			ret.clear();
	}

	return ret;
}

std::vector<ari::CalcKinCharacteristics::M> ari::CalcKinCharacteristics::calcM( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios )
{
	std::vector<ari::CalcKinCharacteristics::M> ret;

	GearBoxWithChangerSpecialFrictionProcess gb( code );
	gb.createChains();

	do
	{
		NS_CORE MappedSystem_p systemM = NS_CORE MappedSystem::createM( gb.getChainsForCurrentGear(), intRatios );
		NS_CORE Gaus::solve( systemM );

		ret.push_back( systemM->getSolution() );

	} while ( gb.turnOnNextGear() );


	return ret;
}

std::vector<ari::CalcKinCharacteristics::W> ari::CalcKinCharacteristics::calcW( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios )
{
	const auto n = intRatios.size();
	std::vector<ari::CalcKinCharacteristics::M> ret;

	GearBoxWithChangerSpecialFrictionProcess gb( code );
	gb.createChains();

	do
	{
		NS_CORE MappedSystem_p systemW = NS_CORE MappedSystem::createW( gb.getChainsForCurrentGear(), intRatios );
		NS_CORE Gaus::solve( systemW );

		auto solution = systemW->getSolution();

		for ( NS_CORE GearSetNumber set( 1 ); set <= NS_CORE GearSetNumber( n ); set++ )
		{
			solution[NS_CORE Element( NS_CORE eMainElement::SATTELITE, set )] = 
				2.0 * ( solution[NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, set )] - solution[NS_CORE Element( NS_CORE eMainElement::CARRIER, set )] ) 
				/ ( intRatios[set.getValue() - 1].getValue() + 1 );
		}

		ret.push_back( solution );

	} while ( gb.turnOnNextGear() );


	return ret;
}

std::vector<CalcKinCharacteristics::N> ari::CalcKinCharacteristics::calcN( const std::vector<W>& w, const std::vector<M>& m )
{
	std::vector<ari::CalcKinCharacteristics::N> ret;
	NS_CORE Log::warning( w.size() != m.size(), "wrpng size", NS_CORE Log::CRITICAL, HERE );

	const auto gearsCount = w.size();

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

	NS_CORE Log::log("Z:", true, NS_CORE eColor::AQUA);
	for ( const auto& z : ch._tooth )
	{
		printCharacteristicsLine( z );
	}

	NS_CORE Log::log( "M:", true, NS_CORE eColor::AQUA );
	for ( const auto& z : ch._torque )
	{
		printCharacteristicsLine( z );
	}

	NS_CORE Log::log( "W:", true, NS_CORE eColor::AQUA );
	for ( const auto& z : ch._angVelocity )
	{
		printCharacteristicsLine( z );
	}

	NS_CORE Log::log( "N:", true, NS_CORE eColor::AQUA );
	for ( const auto& z : ch._power )
	{
		printCharacteristicsLine( z );
	}

	system("pause");
}
