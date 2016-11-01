#pragma once
#include <vector>

#include "IIOItem.h"
#include "Link.h"
#include "GlobalDefines.h"

NS_CORE_START



class Code: public IIOItem
{
private:

	TLinkArray									m_code;													//	Вектор кода
	size_t										m_links;												//	Количество связей
	size_t										m_frictions;											//	Количество фрикционов
	size_t										m_brakes;												//	Количество тормозов

public:

	Code();
	~Code();

	void										setIn(const Element & in);								//	Установка звена, связанного со входом
	void										setOut(const Element & out);							//	Установка звена, связанного со выходом
	void										setLinks( const TLinkArray& links );					//	Установка связей
	void										setFrictions( const TLinkArray& frictions );			//	Установка фрикционов
	void										setBrakes( const TLinkArray& brakes );					//	Установка тормозов

	const TLinkArray&							getCode() const;

	void										print() const;											//	Вывод объекта на экран
		
	// IContainer
	void										writeToFile( std::ostream& ) const override;
	bool										loadFromFile( std::istream& ) override;
	size_t										size() const;

};

NS_CORE_END