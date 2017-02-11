#include "../Libraries/Singletons.h"
#include "../Libraries/Code.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/GearSetTypes.h"
#include "../Libraries/GearBoxWithChanger.h"

#include "CalcKinCharacteristics.h"
#include "MappedSystem.h"

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

		calcM( code, k );

		m_characteristics.push_back( ch );
	}
}

bool ari::CalcKinCharacteristics::checkRequirements() const
{
	return NS_CORE Singletons::getInstance()->getIOFileManager()->isFileExists( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW );
}

ari::CalcKinCharacteristics::Z ari::CalcKinCharacteristics::calcZHelper( const NS_CORE InternalGearRatioValue& intRatio )
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
	
	ret[NS_CORE eMainElement::SUN_GEAR] = z1;
	ret[NS_CORE eMainElement::EPICYCLIC_GEAR] = z2;
	ret[NS_CORE eMainElement::SATTELITE] = z4;

	return ret;
}

std::vector<ari::CalcKinCharacteristics::Z> ari::CalcKinCharacteristics::calcZ( const NS_CORE InternalGearRatios& intRatios )
{
	std::vector<Z> ret;

	for ( size_t i = 0; i < intRatios.size(); i++ ){
		ret.push_back( calcZHelper( intRatios[i] ) );
	}

	for ( size_t i = 0; i < ret.size(); i++ ){
		if ( ret[i].size() != 3 )
			ret.clear();
	}

	return ret;
}

ari::CalcKinCharacteristics::M ari::CalcKinCharacteristics::calcM( const NS_CORE Code code, const NS_CORE InternalGearRatios& intRatios )
{
	M ret;

	NS_CORE GearBoxWithChanger gb( code );
	gb.createChains();

	int i = 0;
	int gear = 0;
	do
	{
		const auto chains = gb.getChainsForCurrentGear();
		MappedSystem_p system = MappedSystem::create( chains, intRatios );
		system->setSolution( NS_CORE Gaus::solve( system->getMatrix() ) );

	} while ( gb.turnOnNextGear() );
	

	return ret;
}
