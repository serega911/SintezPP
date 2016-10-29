#include "TKinematicSchemeBuilder.h"
#include <iostream>
#include "TPathBuilder.h"
#include "TViewer.h"
#include "../Libraries/TSchemeCharacteristics.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TCombinatoricsValueArray.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/IIOItem.h"


NS_ARI_USING

void ari::TKinematicSchemeBuilder::readInitialData()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE TLog::log( "====  Синтез планетарных передач с тремя степенями свободы. Просмотр.  ====\n\n" );
	//	Исходные данные
	readWND();
}

TKinematicScheme TKinematicSchemeBuilder::creatKinematicScheme( const core::TCode & code, const core::TK & k )
{
	TKinematicScheme scheme;
	
	scheme.create( code, k );

	auto numberOfPlanetaryGears = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	for ( size_t i = 0; i < numberOfPlanetaryGears; i++ )
	{
		TPlanetaryGearSet set;
		set.create( NS_CORE TGearSetNumber(i + 1), getPlanetaryGearSetType( k[i] ) );
		scheme.addGearSet( set );
	}

	scheme.addBorders();
	return scheme;
}

NS_CORE KinematicSchemeData TKinematicSchemeBuilder::calcKinemaricSchemeCharacteristics( const TKinematicScheme& scheme )
{
	NS_CORE KinematicSchemeData ret = NS_CORE KinematicSchemeData::s_empty;

	ret = scheme.getKinemaricSchemeCharacteristics();
	return ret;
}

NS_CORE KinematicSchemeData TKinematicSchemeBuilder::bildSchemeSlow( const core::TCode & code, const core::TK & k )
{
	bool res = false;

	code.print();
	const auto& elements = code.getCode();

	size_t num = 0;
	NS_CORE TCombinatoricsValueArray combi;
	TKinematicScheme schemeEthalon = creatKinematicScheme( code, k );

	while ( NS_CORE TSingletons::getInstance()->getCombinatorics()->getPremutation( elements.size(), num++, combi ) )
	{
		TKinematicScheme scheme( schemeEthalon );
		bool finded = true;

		for ( size_t i = 0; i < elements.size(); i++ )
		{

			TPathBuilder pathBuilder;
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
			TViewer::printKinematicScheme( scheme );
			return calcKinemaricSchemeCharacteristics( scheme );
		}
	}

	return NS_CORE KinematicSchemeData::s_empty;
}


NS_CORE KinematicSchemeData ari::TKinematicSchemeBuilder::bildSchemeQuick( const core::TCode & code, const core::TK & k )
{
	bool res = false;

	code.print();
	auto elements = code.getCode();
	auto size = elements.size();
	TKinematicScheme schemeEthalon = creatKinematicScheme( code, k );
	size_t num = 0;

	while ( num++ < size*size )
	{
		TKinematicScheme scheme( schemeEthalon );
		bool finded = true;

		for ( size_t i = 0; i < elements.size(); i++ )
		{

			TPathBuilder pathBuilder;
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

			TViewer::printKinematicScheme( scheme );
			return calcKinemaricSchemeCharacteristics( scheme );
		}
	}

	return NS_CORE KinematicSchemeData::s_empty;
}

TPlanetaryGearSet::Type ari::TKinematicSchemeBuilder::getPlanetaryGearSetType( const NS_CORE TKValue& k )
{
	return k.getAbs().getValue() > 2 ? TPlanetaryGearSet::Type::TYPE_DEFAULT : TPlanetaryGearSet::Type::TYPE_N;
}

void TKinematicSchemeBuilder::run()
{
	readInitialData();

	core::TCode code;
	core::TK k;
	std::vector<core::IIOItem*> containers;
	containers.push_back( &code );
	containers.push_back( &k );

	while ( core::TSingletons::getInstance()->getLoaderFromFile()->load( containers, core::TIOFileManager::eOutputFileType::DONE_K ) )
	{
		NS_CORE KinematicSchemeData res;
		if ( NS_CORE KinematicSchemeData::s_empty != ( res = bildSchemeSlow( code, k ) ) )
		{
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::KIN_SLOW, code );
			NS_CORE TSchemeCharacteristics sc;
			sc.setKinematicScheneData( res );
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::KIN_SLOW, sc );
		}
			

		if ( NS_CORE KinematicSchemeData::s_empty != ( res = bildSchemeQuick( code, k ) ) )
		{
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::KIN_QUICK, code );
			NS_CORE TSchemeCharacteristics sc;
			sc.setKinematicScheneData( res );
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::KIN_QUICK, sc );
		}
			
	}
}

