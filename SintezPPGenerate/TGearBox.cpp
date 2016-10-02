#include "TGearBox.h"
#include "../Libraries/TSingletons.h"

NS_ARI_USING

TGearBox::TGearBox( const NS_CORE TCode& code )
	: Parent( code )
{
}

void TGearBox::setLinksToCode( const NS_CORE TLinkArray& links )
{
	getRefferenceToCode().setLinks( links );
}

void TGearBox::setFrictionsToCode( const NS_CORE TLinkArray& frictions )
{
	getRefferenceToCode().setFrictions( frictions );
}

void TGearBox::setBrakesToCode( const NS_CORE TLinkArray& brakes )
{
	getRefferenceToCode().setBrakes( brakes );
}

NS_CORE TElementArray TGearBox::getElementsForBrakes() const
{
	const auto & chains = getChains();

	NS_CORE TElementArray vect;
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		if ( !chains[i].find( NS_CORE TElement::INPUT ) && !chains[i].find( NS_CORE TElement::OUTPUT ) )
		{
			vect.push_back( chains[i].getSomeElement() );
		}
	}
	return vect;
}

NS_CORE TElementArray TGearBox::getElementsForFrictions() const
{
	const auto & chains = getChains();

	NS_CORE TElementArray vect;
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		vect.push_back( chains[i].getSomeElement() );
	}
	return vect;
}

bool TGearBox::check( const eCheckObject target ) const
{
	auto N = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	const auto & chains = getChains();

	//проверки корректности кода
	for ( size_t i = 0; i < chains.size(); i++ )
	{
		//проверка связи вход-выход
		if ( ( eCheckObject::ALL == target || eCheckObject::IN_OUT_CONNECTION == target ) && chains[i].find( NS_CORE TElement::INPUT ) && chains[i].find( NS_CORE TElement::OUTPUT ) )
		{
			return false;
		}
		//проверка связей между элементами одного ряда
		if ( ( eCheckObject::ALL == target || eCheckObject::ONE_PM_CONNECTION == target ) && !chains[i].checkElemByOnePlanetarySet() )
		{
			return false;
		}
	}
	return true;
}

bool TGearBox::checkFree() const
{
	auto pred = []( const NS_CORE TElement& element, const int i ) -> bool
	{
		return element != NS_CORE TElement::INPUT
			&& element != NS_CORE TElement::OUTPUT
			&& element != NS_CORE TElement::BRAKE
			&& element != NS_CORE TElement::EMPTY
			&& element.getSerialNumber() == i;
	};

	const auto& code = getCode().getCode();

	for ( size_t i = 0; i < 3 * NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears; i++ )
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