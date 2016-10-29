#include <algorithm>

#include "GearBox.h"
#include "Singletons.h"
#include "Log.h"

NS_CORE_USING

GearBox::GearBox( const Code& code )
	: m_code( code )
	, m_gearChanger( code )
{
}

const Code& GearBox::getCode() const
{
	return m_code;
}

Code& GearBox::getRefferenceToCode()
{
	return m_code;
}

const ChainArray& GearBox::getChains() const
{
	Log::warning( m_chains.size() == 0, "There is no chains!", Log::CRITICAL, "TGearBox::getChains()" );
	return m_chains;
}



void GearBox::makeChains( ChainArray &chains ) const
{
	//����� ������� ������
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		for ( size_t j = 0; j < chains.size(); j++ )
		{
			if ( j != i && chains[i].intersect( chains[j] ) )
			{
				chains[i].addChainToChain( chains[j] );
				chains[j].clear();
			}
		}
	}
	//�������� ������ �������
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		if ( chains[i].size() == 0 )
		{
			chains.erase( chains.begin() + i );
			i = i - 1;
		}
	}
	//�������������
	std::sort( chains.begin(), chains.end() );
}

ChainArray GearBox::getChainsForCurrentGear() const
{
	auto chains = getChains();
	auto drivingElements = m_gearChanger.getDrivingElementsForGear();

	chains.resize( chains.size() + drivingElements.size() );

	for ( size_t i = 0; i < drivingElements.size(); i++ )
		chains[chains.size() - i - 1].addLinkToChain( drivingElements[i] );

	makeChains( chains );

	return chains;
}

bool GearBox::createChains()
 {
	 const auto& code = m_code.getCode();

	//������� ��������� ������� (������ ����� �������� ��������)
	const auto size = Singletons::getInstance()->getGeneralData()._numberOfLinks + 2;

	if ( size > code.size() )
		return false;

	m_chains.clear();
	m_chains.resize(size); 
	for ( size_t i = 0; i < size; i++ ){
		m_chains[i].addLinkToChain(code[i]);
	}

	//����� ���������, ��������� �� ������ � �������� �������, ������� �� ��������
	const GearSetNumber N (Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears);
	auto in = code[0].getElem1();
	auto out = code[1].getElem1();
	
	for ( const auto& elem : { eMainElement::SUN_GEAR, eMainElement::EPICYCLIC_GEAR, eMainElement::CARRIER } )
	{
		for ( GearSetNumber i(1); i <= N; i++ )
		{
			size_t b = 0;
			Element element( elem, i );
			for ( size_t j = 0; j < size; j++ )
			{
				if ( element == code[j].getElem1() || element == code[j].getElem2() )
				{
					b++;
					break;
				}
			}
			if ( b == 0 && element != in && element != out )
			{
				m_chains.emplace_back( element );
			}
		}
	}
	//����� ������� ������, �������� ������ �������
	makeChains( m_chains );

	return true;
}

bool core::GearBox::turnOnNextGear()
{
	return m_gearChanger.next();
}

