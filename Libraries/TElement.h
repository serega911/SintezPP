#pragma once

#include <iostream>
#include <vector>

#include "eMainElement.h"
#include "GlobalDefines.h"
#include "TGearSetNumber.h"

NS_CORE_START

class TElement
{
public:

	eMainElement								m_elemN;		//номер элемента
	TGearSetNumber								m_gearSetN;		//номер планетарного ряда

	TElement( const eMainElement& elemN, const TGearSetNumber& gearSetN );
	TElement();

	eMainElement								getElemN() const;
	TGearSetNumber								getGearSetN() const;
	int											getSerialNumber() const;

	void										print() const;
	void										writeTofile( std::ostream& file ) const;
	bool										loadFromFile( std::istream& file );

	static const TElement						INPUT;
	static const TElement						OUTPUT;
	static const TElement						BRAKE;
	static const TElement						EMPTY;

	friend bool									operator<( const TElement& elem1, const TElement& elem2 );
	friend bool									operator==( const TElement& elem1, const TElement& elem2 );
	friend bool									operator!=( const TElement& elem1, const TElement& elem2 );
};

NS_CORE_END