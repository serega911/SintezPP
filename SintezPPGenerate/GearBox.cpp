#include "GearBox.h"
#include "../Libraries/Singletons.h"

NS_ARI_USING

GearBox::GearBox( const NS_CORE Code& code )
	: Parent( code )
{
}

void GearBox::setLinksToCode( const NS_CORE TLinkArray& links )
{
	getRefferenceToCode().setLinks( links );
}

void GearBox::setFrictionsToCode( const NS_CORE TLinkWithFrictionArray& frictions )
{
	getRefferenceToCode().setFrictions( frictions );
}

void GearBox::setBrakesToCode( const NS_CORE TLinkArray& brakes )
{
	getRefferenceToCode().setBrakes( brakes );
}

NS_CORE ElementArray GearBox::getElementsForBrakes() const
{
	const auto & chains = getChains();

	NS_CORE ElementArray vect;
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		if ( !chains[i].find( NS_CORE Element::INPUT ) && !chains[i].find( NS_CORE Element::OUTPUT ) )
		{
			vect.push_back( chains[i].getSomeElement() );
		}
	}
	return vect;
}

NS_CORE ElementArray GearBox::getElementsForFrictions() const
{
	const auto & chains = getChains();

	NS_CORE ElementArray vect;
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		vect.push_back( chains[i].getSomeElement() );
	}
	return vect;
}

bool GearBox::check( const eCheckTarget target ) const
{
	auto N = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	const auto & chains = getChains();

	//проверки корректности кода
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		//проверка связи вход-выход
		if ( ( eCheckTarget::ALL == target || eCheckTarget::IN_OUT_CONNECTION == target ) && chains[i].find( NS_CORE Element::INPUT ) && chains[i].find( NS_CORE Element::OUTPUT ) )
		{
			return false;
		}
		//проверка связей между элементами одного ряда
		if ( ( eCheckTarget::ALL == target || eCheckTarget::ONE_PM_CONNECTION == target ) && !chains[i].checkElemByOnePlanetarySet() )
		{
			return false;
		}
	}
	return true;
}

bool GearBox::checkFree() const
{
	const NS_CORE GearSetNumber N( NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears );
	/*const auto& code = getCode().getCode();*/

	for ( const auto& elem : { NS_CORE eMainElement::SUN_GEAR, NS_CORE eMainElement::EPICYCLIC_GEAR, NS_CORE eMainElement::CARRIER } )
	{
		for ( NS_CORE GearSetNumber i( 1 ); i <= N; i++ )
		{
			size_t count = 0;
			if ( !getCode().isContain( NS_CORE Element( elem, i ) ) )
				return false;
		}
	}
	return true;
}	//проверяет остались ли пустые элементы