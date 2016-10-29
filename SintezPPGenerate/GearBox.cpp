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

void GearBox::setFrictionsToCode( const NS_CORE TLinkArray& frictions )
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
	auto pred = []( const NS_CORE Element& element, const int i ) -> bool
	{
		return element != NS_CORE Element::INPUT
			&& element != NS_CORE Element::OUTPUT
			&& element != NS_CORE Element::BRAKE
			&& element != NS_CORE Element::EMPTY
			&& element.getSerialNumber() == i;
	};

	const auto& code = getCode().getCode();

	for ( size_t i = 0; i < 3 * NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears; i++ )
	{
		size_t count = 0;
		for ( size_t j = 0; j < code.size(); j++ )
			if ( pred( code[j].getElem1(), i ) || pred( code[j].getElem2(), i ) )
				count++;
		if ( count == 0 )
			return false;
	}
	return true;
}	//проверяет остались ли пустые элементы