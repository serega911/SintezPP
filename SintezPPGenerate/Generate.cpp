#include "Generate.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"


NS_ARI_USING

const NS_CORE eMainElementArray Generate::s_elements = { NS_CORE eMainElement::SUN_GEAR, NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE eMainElement::CARRIER };

void Generate::run()
{
	showParams();
	NS_CORE Singletons::getInstance()->getIOFileManager()->cleanFiles();
	auto N = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	//	Заполняем вектор всех возможных связей, пропускаем связи между элементами одного ряда и реверсивные связи.
	m_allLinks.clear();
	for ( size_t i = 1; i < N; i++ )
	{
		for ( const auto& mElem1 : s_elements )
		{
			for ( size_t j = i + 1; j <= N; j++ )
			{
				for ( const auto& mElem2 : s_elements )
				{
					m_allLinks.push_back( NS_CORE Link( NS_CORE Element( mElem1, NS_CORE GearSetNumber( i ) ), NS_CORE Element( mElem2, NS_CORE GearSetNumber( j ) ) ) );
				}
			}
		}
	}

	generateInOut();
}

bool ari::Generate::checkRequirements() const
{
	return true;
}

void Generate::generateInOut()
{
	
	auto N = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	for ( size_t i = 1; i <= N; i++ )
	{
		for ( const auto& inElem : s_elements )
		{
			for ( size_t j = 1; j <= N; j++ )
			{
				for ( const auto& outElem : s_elements )
				{
					NS_CORE Element elemIn( inElem, NS_CORE GearSetNumber( i ) );
					NS_CORE Element elemOut( outElem, NS_CORE GearSetNumber( j ) );
					if (elemIn != elemOut)
					{
						NS_CORE Code code;
						code.setIn(elemIn);
						code.setOut(elemOut);
						GearBox gearBox( code );
						generateLinks( gearBox );
					}
				}
			}
		}
	}
}

void Generate::generateLinks( const GearBox & gearBox )
{
	NS_CORE CombinatoricsValueArray linksCombi;		//	Вектор сочетаний связей

	size_t i = 0;
	size_t allLinksSize = m_allLinks.size();
	size_t countOfLinks = NS_CORE Singletons::getInstance()->getGeneralData()._numberOfLinks;

	while ( NS_CORE Singletons::getInstance()->getCombinatorics()->getSubset( allLinksSize, countOfLinks, i++, linksCombi ) )
	{
		GearBox gearBoxWithLinks( gearBox );
		//	Заполняем вектор связей с учетом сгенерированного сочетания
		NS_CORE TLinkArray links;			//	Вектор связей
		for ( size_t i = 0; i < linksCombi.size(); i++ )
			links.push_back(m_allLinks[linksCombi[i]]);
		gearBoxWithLinks.setLinksToCode( links );
		gearBoxWithLinks.createChains();
		if ( gearBoxWithLinks.check(GearBox::ALL) )
		{
			if ( m_existingSchemes.findIn( gearBoxWithLinks.getChains() ) )
			{
				//NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::FAIL_REPETTION, gearBoxWithLinks.getCode() );
			}
			else
			{
				m_existingSchemes.add( gearBoxWithLinks.getChains() );
				generateFrictions( gearBoxWithLinks );
			}
		}
		else
		{
			NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::FAIL_0, gearBoxWithLinks.getCode() );
		}
	}
}

void Generate::generateFrictions( const GearBox & gearBox )
{
	//	Определяем элементы, на которых будет установлен фрикцион
	NS_CORE ElementArray vect_all_FB = gearBox.getElementsForFrictions();

	const auto& generalData = NS_CORE Singletons::getInstance()->getGeneralData();

// 	if ( vect_all_FB.size() == generalData._numberOfBrakes + generalData._numberOfFrictions + 2 )
// 	{
		NS_CORE TLinkArray vect_all_frict;							//	Вектор всех возможных фрикционов
		NS_CORE CombinatoricsValueArray vect_combi_frict;			//	Вектор сочетаний фрикционов
		NS_CORE TLinkWithFrictionArray vect_frict;								//	Вектор фрикционов
		for ( size_t i = 0; i < vect_all_FB.size(); i++ )
			for ( size_t j = i + 1; j < vect_all_FB.size(); j++ )
				vect_all_frict.push_back( NS_CORE Link( vect_all_FB[i], vect_all_FB[j] ) );
		//	Создаем первое сочетание фрикционов из связей по Count_F (количество фрикционов) без повторений: 0,1...
		//	В цикле генерируем все возможные сочетания фрикционов

		size_t i = 0;
		size_t allFrictSize = vect_all_frict.size();
		size_t countOfFrictions = NS_CORE Singletons::getInstance()->getGeneralData()._numberOfFrictions;

		while ( NS_CORE Singletons::getInstance()->getCombinatorics()->getSubset( allFrictSize, countOfFrictions, i++, vect_combi_frict ) )
		{
			GearBox gearBoxWithFrictions( gearBox );
			//	Заполняем вектор фрикционов с учетом сгенерированного сочетания
			vect_frict.clear();
			for ( size_t i = 0; i < vect_combi_frict.size(); i++ )
				vect_frict.emplace_back(NS_CORE LinkWithFriction(vect_all_frict[vect_combi_frict[i]], i+1));
			gearBoxWithFrictions.setFrictionsToCode( vect_frict );
			
			if ( gearBoxWithFrictions.check( GearBox::ALL ) )
			{
				generateBrakes( gearBoxWithFrictions );
			}
			
		}
// 	}
// 	else
// 	{
// 		NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::FAIL_N, gearBox.getCode() );
// 	}
}

void Generate::generateBrakes( const GearBox & gearBox )
{
	NS_CORE ElementArray vect_all_FB = gearBox.getElementsForBrakes();
	NS_CORE CombinatoricsValueArray vect_combi_brakes;		//	Вектор сочетаний тормозов
	//	Создаем первое сочетание тормозов из всех возможных по Count_B

	size_t i = 0;
	size_t allBrakesSize = vect_all_FB.size();
	size_t countOfBrakes = NS_CORE Singletons::getInstance()->getGeneralData()._numberOfBrakes;

	while ( NS_CORE Singletons::getInstance()->getCombinatorics()->getSubset( allBrakesSize, countOfBrakes, i++, vect_combi_brakes ) )
	{
		GearBox gearBoxWithBrakes( gearBox );
		NS_CORE TLinkArray vect_brakes;	//	Вектор тормозов
		//	Заполняем вектор тормозов с учетом сгенерированного сочетания
		for ( size_t i = 0; i < vect_combi_brakes.size(); i++ )
			vect_brakes.push_back( NS_CORE Link( vect_all_FB[vect_combi_brakes[i]], NS_CORE Element(NS_CORE eMainElement::BRAKE, NS_CORE GearSetNumber(i+1)) ) );
		gearBoxWithBrakes.setBrakesToCode( vect_brakes );
		//C.print();
		if ( gearBoxWithBrakes.checkFree() )
			NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DONE, gearBoxWithBrakes.getCode() );
		else
		{
			//NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::FAIL_FREE, gearBoxWithBrakes.getCode() );
		}
	} 
}


