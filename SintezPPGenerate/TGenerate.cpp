#include "TGenerate.h"
#include "../Libraries/TSingletons.h"
#include "../Libraries/TCombinations.h"
#include "../Libraries/TLog.h"


NS_ARI_USING

const std::vector<NS_CORE eMainElement> TGenerate::s_elements = { NS_CORE eMainElement::SUN_GEAR, NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE eMainElement::CARRIER };

void TGenerate::readInitialData()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE TLog::log( "====  Синтез планетарных передач с тремя степенями свободы. Генерация.  ====\n\n" );
	//	Исходные данные
	int W = 0;
	int N = 0;
	NS_CORE TLog::log( "\t\t\tИсходные данные." );
	NS_CORE TLog::log( "Число степеней свободы:	", false );
	std::cin >> W;
	NS_CORE TLog::log( "Количество ПМ:		", false );
	std::cin >> N;
	NS_CORE TSingletons::getInstance()->setGlobalParameters( W, N );

	auto generalData = NS_CORE TSingletons::getInstance()->getGeneralData();
	NS_CORE TLog::log( "Количество связей:	" + std::to_string( generalData._numberOfLinks ) );
	NS_CORE TLog::log( "Количество фрикционов:	" + std::to_string( generalData._numberOfFrictions ) );
	NS_CORE TLog::log( "Количество тормозов:	" + std::to_string( generalData._numberOfBrakes ) );
}

void TGenerate::run()
{
	readInitialData();

	auto N = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

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
					m_allLinks.push_back( NS_CORE TLink( NS_CORE TElement( mElem1, i ), NS_CORE TElement( mElem2, j ) ) );
				}
			}
		}
	}

	generateInOut();
}

void TGenerate::generateInOut()
{
	
	auto N = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	for ( size_t i = 1; i <= N; i++ )
	{
		for ( const auto& inElem : s_elements )
		{
			for ( size_t j = 1; j <= N; j++ )
			{
				for ( const auto& outElem : s_elements )
				{
					NS_CORE TElement elemIn( inElem, i );
					NS_CORE TElement elemOut( outElem, j );
					if (elemIn != elemOut)
					{
						NS_CORE TCode code;
						code.setIn(elemIn);
						code.setOut(elemOut);
						TGearBox gearBox( code );
						generateLinks( gearBox );
					}
				}
			}
		}
	}
}

void TGenerate::generateLinks( const TGearBox & gearBox )
{
	NS_CORE TCombinations linksCombi;		//	Вектор сочетаний связей
	linksCombi.init( NS_CORE TSingletons::getInstance()->getGeneralData()._numberOfLinks );
	do{
		TGearBox gearBoxWithLinks( gearBox );
		//	Заполняем вектор связей с учетом сгенерированного сочетания
		NS_CORE TLinkArray links;			//	Вектор связей
		for (int i = 0; i < linksCombi.size(); i++)
			links.push_back(m_allLinks[linksCombi[i]]);
		gearBoxWithLinks.setLinksToCode( links );
		gearBoxWithLinks.createChains();
		if ( gearBoxWithLinks.check() )
		{
			if ( m_existingSchemes.findIn( gearBoxWithLinks.getChains() ) )
			{
				NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::FAIL_REPETTION, gearBoxWithLinks.getCode() );
			}
			else
			{
				m_existingSchemes.add( gearBoxWithLinks.getChains() );
				generateFrictions( gearBoxWithLinks );
			}
		}
		else
		{
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::FAIL_0, gearBoxWithLinks.getCode() );
		}
	} while (linksCombi.nextReplace(m_allLinks.size()-1));
}

void TGenerate::generateFrictions( const TGearBox & gearBox )
{
	//	Определяем элементы, на которых будет установлен фрикцион
	NS_CORE TElementArray vect_all_FB = gearBox.getElementsForFrictions();

	const auto& generalData = NS_CORE TSingletons::getInstance()->getGeneralData();

	if ( vect_all_FB.size() == generalData._numberOfBrakes + generalData._numberOfFrictions + 2 )
	{
		NS_CORE TLinkArray vect_all_frict;				//	Вектор всех возможных фрикционов
		NS_CORE TCombinations vect_combi_frict;			//	Вектор сочетаний фрикционов
		NS_CORE TLinkArray vect_frict;					//	Вектор фрикционов
		for ( size_t i = 0; i < vect_all_FB.size(); i++ )
			for ( size_t j = i + 1; j < vect_all_FB.size(); j++ )
				vect_all_frict.push_back( NS_CORE TLink( vect_all_FB[i], vect_all_FB[j] ) );
		//	Создаем первое сочетание фрикционов из связей по Count_F (количество фрикционов) без повторений: 0,1...
		vect_combi_frict.init( generalData._numberOfFrictions );
		//	В цикле генерируем все возможные сочетания фрикционов
		do{
			TGearBox gearBoxWithFrictions( gearBox );
			//	Заполняем вектор фрикционов с учетом сгенерированного сочетания
			vect_frict.clear();
			for (int i = 0; i < vect_combi_frict.size(); i++)
				vect_frict.push_back(vect_all_frict[vect_combi_frict[i]]);
			gearBoxWithFrictions.setFrictionsToCode( vect_frict );
			generateBrakes( gearBoxWithFrictions );
		} while (vect_combi_frict.nextReplace(vect_all_frict.size() - 1));
	}
	else
	{
		NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::FAIL_N, gearBox.getCode() );
	}
}

void TGenerate::generateBrakes( const TGearBox & gearBox )
{
	NS_CORE TElementArray vect_all_FB = gearBox.getElementsForBrakes();
	NS_CORE TCombinations vect_combi_brakes;		//	Вектор сочетаний тормозов
	//	Создаем первое сочетание тормозов из всех возможных по Count_B
	vect_combi_brakes.init( NS_CORE TSingletons::getInstance()->getGeneralData()._numberOfBrakes );
	do{
		TGearBox gearBoxWithBrakes( gearBox );
		NS_CORE TLinkArray vect_brakes;	//	Вектор тормозов
		//	Заполняем вектор тормозов с учетом сгенерированного сочетания
		for (int i = 0; i < vect_combi_brakes.size(); i++)
			vect_brakes.push_back( NS_CORE TLink( vect_all_FB[vect_combi_brakes[i]], NS_CORE TElement::BRAKE ) );
		gearBoxWithBrakes.setBrakesToCode( vect_brakes );
		//C.print();
		if ( gearBoxWithBrakes.checkFree() )
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE, gearBoxWithBrakes.getCode() );
		else
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::FAIL_FREE, gearBoxWithBrakes.getCode() );
	} while (vect_combi_brakes.nextReplace(vect_all_FB.size() - 1));
}


