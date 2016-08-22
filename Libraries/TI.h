#pragma once

#include <vector>

#include "GlobalDefines.h"

NS_CORE_START

typedef double TIValue;							// передаточное отношение КПП
typedef std::vector<TIValue> TIValueArray;		// контейнер передаточных отношений ПКП

class TI
{
private:

	TIValueArray								m_i;
	static double								m_eps;

public:

	TI();
	TI( const TIValueArray& i, double eps );

	size_t										size() const;

	const TIValue &								operator[]( size_t i ) const;
	bool										operator==(const TI& obj) const; // outdated
	void										operator=(const TI& obj);

	void										push_back( TIValue value );

	void										print() const;

	bool										findIn( TIValue value ) const;

};

NS_CORE_END
