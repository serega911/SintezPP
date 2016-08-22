#pragma once

#include <vector>
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TI.h"

NS_ARI_START

class TI
{
private:
	NS_CORE TIValueArray						m_i;
	static double								m_eps;
public:
	TI();
	TI( const NS_CORE TIValueArray& i, double eps );
	size_t										size() const;
	const double								operator[](int i) const;
	bool										operator==(const TI& obj); // RK: const and OUTSIDE class
	void										operator=(const TI& obj);
	void										push_back(double value);
	void										print();
	bool										findIn( double value ) const;

};

NS_ARI_END