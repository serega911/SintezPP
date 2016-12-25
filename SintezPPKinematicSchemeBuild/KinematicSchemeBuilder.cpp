#include "KinematicSchemeBuilder.h"
#include <iostream>
#include "PathBuilder.h"
#include "Viewer.h"
#include "../Libraries/SchemeCharacteristics.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/CombinatoricsValueArray.h"
#include "../Libraries/Code.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/IIOItem.h"


NS_ARI_USING

void ari::KinematicSchemeBuilder::readUISpecialData()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE Log::log( "====  Синтез планетарных передач с тремя степенями свободы. Просмотр.  ====\n\n" );
	//	Исходные данные
	readUIGeneralData();
}

KinematicScheme KinematicSchemeBuilder::creatKinematicScheme( const core::Code & code, const core::InternalGearRatios & k )
{
	KinematicScheme scheme;
	
	scheme.create( code, k );

	auto numberOfPlanetaryGears = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	for ( size_t i = 0; i < numberOfPlanetaryGears; i++ )
	{
		PlanetaryGearSet set;
		set.create( NS_CORE GearSetNumber(i + 1), getPlanetaryGearSetType( k[i] ) );
		scheme.addGearSet( set );
	}

	scheme.addBorders();
	return scheme;
}

NS_CORE KinematicSchemeData KinematicSchemeBuilder::calcKinemaricSchemeCharacteristics( const KinematicScheme& scheme )
{
	NS_CORE KinematicSchemeData ret = NS_CORE KinematicSchemeData::s_empty;

	ret = scheme.getKinemaricSchemeCharacteristics();
	return ret;
}

NS_CORE KinematicSchemeData KinematicSchemeBuilder::bildSchemeSlow( const core::Code & code, const core::InternalGearRatios & k )
{
	bool res = false;

	code.print();
	const auto& elements = code.getCode();

	size_t num = 0;
	NS_CORE CombinatoricsValueArray combi;
	KinematicScheme schemeEthalon = creatKinematicScheme( code, k );

	while ( NS_CORE Singletons::getInstance()->getCombinatorics()->getPremutation( elements.size(), num++, combi ) )
	{
		KinematicScheme scheme( schemeEthalon );
		bool finded = true;

		for ( size_t i = 0; i < elements.size(); i++ )
		{

			PathBuilder pathBuilder;
			auto path = pathBuilder.findPath( scheme, elements[combi[i]] );
			if ( path.size() != 0 )
			{
				scheme.addRoute( path, elements[combi[i]] );
			}
			else
			{
				finded = false;
				break;
			}
		}

		if ( finded )
		{
			Viewer::printKinematicScheme( scheme );
			return calcKinemaricSchemeCharacteristics( scheme );
		}
	}

	return NS_CORE KinematicSchemeData::s_empty;
}


NS_CORE KinematicSchemeData ari::KinematicSchemeBuilder::bildSchemeQuick( const core::Code & code, const core::InternalGearRatios & k )
{
	bool res = false;

	code.print();
	auto elements = code.getCode();
	auto size = elements.size();
	KinematicScheme schemeEthalon = creatKinematicScheme( code, k );
	size_t num = 0;

	while ( num++ < size*size )
	{
		KinematicScheme scheme( schemeEthalon );
		bool finded = true;

		for ( size_t i = 0; i < elements.size(); i++ )
		{

			PathBuilder pathBuilder;
			auto path = pathBuilder.findPath( scheme, elements[i] );
			if ( path.size() != 0 )
			{
				scheme.addRoute( path, elements[i] );
			}
			else
			{
				finded = false;
				std::swap( elements[i], elements[i - 1] );
				break;
			}
		}

		if ( finded )
		{

			Viewer::printKinematicScheme( scheme );
			return calcKinemaricSchemeCharacteristics( scheme );
		}
	}

	return NS_CORE KinematicSchemeData::s_empty;
}

PlanetaryGearSet::Type ari::KinematicSchemeBuilder::getPlanetaryGearSetType( const NS_CORE InternalGearRatioValue& k )
{
	return k.getAbs().getValue() > 2 ? PlanetaryGearSet::Type::TYPE_DEFAULT : PlanetaryGearSet::Type::TYPE_N;
}

void KinematicSchemeBuilder::run()
{
	readUISpecialData();

	core::Code code;
	core::InternalGearRatios k;
	std::vector<core::IIOItem*> containers;
	containers.push_back( &code );
	containers.push_back( &k );

	while ( core::Singletons::getInstance()->getLoaderFromFile()->load( containers, core::IOFileManager::eOutputFileType::DONE_K ) )
	{
		NS_CORE KinematicSchemeData res;
		if ( NS_CORE KinematicSchemeData::s_empty != ( res = bildSchemeSlow( code, k ) ) )
		{
			NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW, code );
			NS_CORE SchemeCharacteristics sc;
			sc.setKinematicScheneData( res );
			NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::KIN_SLOW, sc );
		}
			

		if ( NS_CORE KinematicSchemeData::s_empty != ( res = bildSchemeQuick( code, k ) ) )
		{
			NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::KIN_QUICK, code );
			NS_CORE SchemeCharacteristics sc;
			sc.setKinematicScheneData( res );
			NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::KIN_QUICK, sc );
		}
			
	}
}

