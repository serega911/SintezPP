#pragma once
#include <vector>

#include "IContainer.h"
#include "TLink.h"
#include "GlobalDefines.h"
#include "GlobalTypes.h"

NS_CORE_START

typedef std::vector<TLink> TLinks;

class TCode: public IContainer
{
private:

	TLinks										m_code;													//	Вектор кода
	TCount										m_links;												//	Количество связей
	TCount										m_frictions;											//	Количество фрикционов
	TCount										m_brakes;												//	Количество тормозов

public:

	TCode();
	~TCode();

	void										setIn(const TElement & in);								//	Установка звена, связанного со входом
	void										setOut(const TElement & out);							//	Установка звена, связанного со выходом
	void										setLinks( const TLinks& links );						//	Установка связей
	void										setFrictions( const TLinks& frictions );				//	Установка фрикционов
	void										setBrakes( const TLinks& brakes );						//	Установка тормозов

	const TLinks&								getCode() const;

	void										print() const;											//	Вывод объекта на экран
		
	// IContainer
	void										writeToFile( std::ostream& ) const override;
	bool										loadFromFile( std::istream& ) override;
	size_t										size() const override;

};

NS_CORE_END