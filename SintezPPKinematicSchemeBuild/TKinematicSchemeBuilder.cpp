#include "TKinematicSchemeBuilder.h"
#include <iostream>
#include "TPathBuilder.h"
#include "TViewer.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/IContainer.h"


NS_ARI_USING

void ari::TKinematicSchemeBuilder::readInitialData()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE TLog::log( "====  Синтез планетарных передач с тремя степенями свободы. Просмотр.  ====\n\n" );
	//	Исходные данные
	int W = 0;
	int N = 0;
	NS_CORE TLog::log( "\t\t\tИсходные данные." );
	NS_CORE TLog::log( "Число степеней свободы:	", false );
	std::cin >> W;
	NS_CORE TLog::log( "Количество ПМ:		", false );
	std::cin >> N;
	NS_CORE TSingletons::getInstance()->setGlobalParameters( W, N );
}

TKinematicScheme TKinematicSchemeBuilder::creatKinematicScheme( const core::TCode & code, const core::TK & k )
{
	TKinematicScheme scheme;
	
	scheme.create( code, k );

	auto numberOfPlanetaryGears = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	for ( auto i = 0; i < numberOfPlanetaryGears; i++ )
	{
		TPlanetaryGearSet set;
		set.create( i + 1, getPlanetaryGearSetType( k[i] ) );
		scheme.addGearSet( set );
	}

	scheme.addBorders();
	return scheme;
}

TPlanetaryGearSet::Type ari::TKinematicSchemeBuilder::getPlanetaryGearSetType( const NS_CORE TKValue& k )
{
	return abs( k ) > 2 ? TPlanetaryGearSet::Type::TYPE_DEFAULT : TPlanetaryGearSet::Type::TYPE_N;
}

void TKinematicSchemeBuilder::run()
{
	readInitialData();

	core::TCode code;
	core::TK k;
	std::vector<core::IContainer*> containers;
	containers.push_back( &code );
	containers.push_back( &k );

	while ( core::TSingletons::getInstance()->getLoaderFromFile()->load( containers, core::TIOFileManager::eOutputFileType::DONE_K ) )
	{
		TKinematicScheme scheme = creatKinematicScheme(code,k);
		TKinematicScheme fakeScheme = creatKinematicScheme(code,k);

		//system( "cls" );
		//scheme.print();
		//system( "pause" );

		const auto& elements = code.getCode();

		for ( int i = 0; i < elements.size(); i++ )
		{
			TPathBuilder pathBuilder;
			auto path = pathBuilder.findPath( fakeScheme, elements[i] );
			if ( path.size() != 0 )
			{
				scheme.addRoute( path, elements[i] );
				fakeScheme.addFakeRoute( path, elements[i] );
			}
			//system( "cls" );
			//scheme.print();
		}
		code.print();
		TViewer::printKinematicScheme( scheme );
		system( "pause" );
		//k.print();
	}
}

