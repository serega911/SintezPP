#pragma once

#include <iostream>
#include <vector>

#include "eMainElement.h"
#include "GlobalDefines.h"
#include "GearSetNumber.h"

NS_CORE_START

class Element
{
public:

	eMainElement								m_elemN;		//номер элемента
	GearSetNumber								m_gearSetN;		//номер планетарного ряда

	Element( const eMainElement& elemN, const GearSetNumber& gearSetN );
	Element();

	eMainElement								getElemN() const;
	GearSetNumber								getGearSetN() const;
	

	void										print() const;
	void										writeTofile( std::ostream& file ) const;
	bool										loadFromFile( std::istream& file );

	static const Element						INPUT;
	static const Element						OUTPUT;
	static const Element						BRAKE;
	static const Element						EMPTY;

	bool										isCentral() const;
	bool										isAdditional() const;

	friend bool									operator<( const Element& elem1, const Element& elem2 );
	friend bool									operator==( const Element& elem1, const Element& elem2 );
	friend bool									operator!=( const Element& elem1, const Element& elem2 );
};

NS_CORE_END