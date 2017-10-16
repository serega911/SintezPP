#include "Generate.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"
#include "../Libraries/Subset.h"


NS_ARI_USING

const NS_CORE eMainElementArray Generate::s_elements = { NS_CORE eMainElement::SUN_GEAR, NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE eMainElement::CARRIER };

void Generate::run()
{
	showParams();
	NS_CORE Singletons::getInstance()->getIOFileManager()->cleanFiles();
	auto N = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	//	��������� ������ ���� ��������� ������, ���������� ����� ����� ���������� ������ ���� � ����������� �����.
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
					if ( elemIn != elemOut )
					{
						NS_CORE Code code;
						code.setIn( elemIn );
						code.setOut( elemOut );
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
	size_t countOfLinks = NS_CORE Singletons::getInstance()->getGeneralData()._numberOfLinks;

	NS_CORE Subset<NS_CORE TLinkArray> subset( m_allLinks, countOfLinks );

	const auto& initialData = NS_CORE Singletons::getInstance()->getInitialData();

	do
	{
		GearBox gearBoxWithLinks( gearBox );
		gearBoxWithLinks.setLinksToCode( subset.get() );
		gearBoxWithLinks.createChains();
		if ( gearBoxWithLinks.check( GearBox::ALL ) )
		{
			if ( gearBoxWithLinks.getChains().size() != initialData._numberOfPlanetaryGears + initialData._w )
			{
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::FAIL_N, gearBoxWithLinks.getCode() );
			}
			else if ( m_existingSchemes.findIn( gearBoxWithLinks.getChains() ) )
			{
				NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::FAIL_REPETTION, gearBoxWithLinks.getCode() );
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
	} while ( subset.next() );
}

void Generate::generateFrictions( const GearBox & gearBox )
{
	//	���������� ��������, �� ������� ����� ���������� ��������
	NS_CORE ElementArray vect_all_FB = gearBox.getElementsForFrictions();
	size_t countOfFrictions = NS_CORE Singletons::getInstance()->getGeneralData()._numberOfFrictions;
	const auto& generalData = NS_CORE Singletons::getInstance()->getGeneralData();
		
	NS_CORE TLinkArray vect_all_frict;							//	������ ���� ��������� ����������

	for ( size_t i = 0; i < vect_all_FB.size(); i++ )
		for ( size_t j = i + 1; j < vect_all_FB.size(); j++ )
			vect_all_frict.emplace_back( vect_all_FB[i], vect_all_FB[j] );

	NS_CORE Subset<NS_CORE TLinkArray> subset( vect_all_frict, countOfFrictions );
	//	������� ������ ��������� ���������� �� ������ �� Count_F (���������� ����������) ��� ����������: 0,1...
	//	� ����� ���������� ��� ��������� ��������� ����������

	do
	{
		GearBox gearBoxWithFrictions( gearBox );
		//	��������� ������ ���������� � ������ ���������������� ���������
		NS_CORE TLinkWithFrictionArray vect_frict;								//	������ ����������
		const auto frictions = subset.get();
		for ( size_t i = 0; i < frictions.size(); i++ )
			vect_frict.emplace_back( NS_CORE LinkWithFriction( frictions[i], i + 1 ) );
		gearBoxWithFrictions.setFrictionsToCode( vect_frict );

		if ( gearBoxWithFrictions.check( GearBox::ALL ) )
		{
			generateBrakes( gearBoxWithFrictions );
		}

	} while ( subset.next() );
}

void Generate::generateBrakes( const GearBox & gearBox )
{
	NS_CORE ElementArray vect_all_FB = gearBox.getElementsForBrakes();
	size_t countOfBrakes = NS_CORE Singletons::getInstance()->getGeneralData()._numberOfBrakes;
	NS_CORE Subset<NS_CORE ElementArray> subset( vect_all_FB, countOfBrakes );
	//	������� ������ ��������� �������� �� ���� ��������� �� Count_B

	size_t i = 0;
	size_t allBrakesSize = vect_all_FB.size();
	

	do
	{
		GearBox gearBoxWithBrakes( gearBox );
		NS_CORE TLinkArray vect_brakes;	//	������ ��������
		const auto brakes = subset.get();
		//	��������� ������ �������� � ������ ���������������� ���������
		for ( size_t i = 0; i < brakes.size(); i++ )
			vect_brakes.push_back( NS_CORE Link( brakes[i], NS_CORE Element( NS_CORE eMainElement::BRAKE, NS_CORE GearSetNumber( i + 1 ) ) ) );
		gearBoxWithBrakes.setBrakesToCode( vect_brakes );

		if ( gearBoxWithBrakes.checkFree() )
			NS_CORE Singletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE IOFileManager::eOutputFileType::DONE, gearBoxWithBrakes.getCode() );
		else
		{
			//NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::FAIL_FREE, gearBoxWithBrakes.getCode() );
		}
	} while ( subset.next() );
}


