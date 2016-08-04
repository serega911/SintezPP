#include "TGearBox.h"
#include "../Libraries/TSingletons.h"

NS_ARI_USING

TGearBox::TGearBox( const NS_CORE TCode& code )
	: Parent( code )
{
}

void TGearBox::setLinksToCode( const NS_CORE TLinks& links )
{
	getRefferenceToCode().setLinks( links );
}

void TGearBox::setFrictionsToCode( const NS_CORE TLinks& frictions )
{
	getRefferenceToCode().setFrictions( frictions );
}

void TGearBox::setBrakesToCode( const NS_CORE TLinks& brakes )
{
	getRefferenceToCode().setBrakes( brakes );
}

NS_CORE TElements TGearBox::getElementsForBrakes() const
{
	const auto & chains = getChains();

	NS_CORE TElements vect;
	for ( auto i = 0; i < chains.size(); i++ )
	{
		if ( !chains[i].find( NS_CORE TElement::INPUT ) && !chains[i].find( NS_CORE TElement::OUTPUT ) )
		{
			vect.push_back( chains[i].getSomeElement() );
		}
	}
	return vect;
}

NS_CORE TElements TGearBox::getElementsForFrictions() const
{
	const auto & chains = getChains();

	NS_CORE TElements vect;
	for ( auto i = 0; i < chains.size(); i++ )
	{
		vect.push_back( chains[i].getSomeElement() );
	}
	return vect;
}

bool TGearBox::check() const
{
	auto N = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	const auto & chains = getChains();

	//проверки корректности кода
	for ( auto i = 0; i < chains.size(); i++ )
	{
		//проверка связи вход-выход
		if ( chains[i].find( NS_CORE TElement::INPUT ) && chains[i].find( NS_CORE TElement::OUTPUT ) )
		{
			return false;
		}
		//проверка связей между элементами одного ряда
		if ( !chains[i].checkElemByOnePlanetarySet() )
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

	for ( auto i = 0; i < 3 * NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears; i++ )
	{
		NS_CORE TCount count = 0;
		for ( auto j = 0; j < code.size(); j++ )
			if ( pred( code[j].getElem1(), i ) || pred( code[j].getElem2(), i ) )
				count++;
		if ( count == 0 )
			return false;
	}
	return true;
}	//проверяет остались ли пустые элементы