#pragma once
#include <vector>

#include "IIOItem.h"
#include "Link.h"
#include "GlobalDefines.h"

NS_CORE_START



class Code: public IIOItem
{
private:

	Link										m_input;
	Link										m_output;
	TLinkArray									m_links;
	TLinkArray									m_frictions;
	TLinkArray									m_brakes;

	bool										isArrayContain( const TLinkArray& array, const Element& elem) const;

public:

	Code();
	~Code();

	void										setIn(const Element & in);								//	Установка звена, связанного со входом
	void										setOut(const Element & out);							//	Установка звена, связанного со выходом
	void										setLinks( const TLinkArray& links );					//	Установка связей
	void										setFrictions( const TLinkArray& frictions );			//	Установка фрикционов
	void										setBrakes( const TLinkArray& brakes );					//	Установка тормозов

	const Link&									getIn() const;
	const Link&									getOut() const;
	const TLinkArray&							getLinks() const;
	const TLinkArray&							getFrictions() const;
	const TLinkArray&							getBrakes() const;

	bool										isContain( const Element& elem ) const ;

	void										print() const;											//	Вывод объекта на экран
		
	// IIOItem
	void										writeToFile( std::ostream& ) const override;
	bool										loadFromFile( std::istream& ) override;

};

NS_CORE_END