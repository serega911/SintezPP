#pragma once

#include <vector>

#include "GlobalDefines.h"
#include "GlobalTypes.h"

NS_CORE_START

class TI
{
private:

	std::vector<TIValue>						m_i;
	static double								m_eps;

public:

	TI();
	TI(const std::vector<double>& i, double eps);

	int											size() const;

	const TIValue &								operator[]( size_t i ) const;
	bool										operator==(const TI& obj) const; // outdated
	void										operator=(const TI& obj);

	void										push_back( TIValue value );

	void										print() const;

	bool										findIn( TIValue value ) const;

};

NS_CORE_END
