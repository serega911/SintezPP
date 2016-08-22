#pragma once
#include <vector>
#include <iostream>

#include "../Libraries/IContainer.h"
#include "../Libraries/TK.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class TK : public NS_CORE TK
{
private:
	bool										m_isFinded;
	double										m_dK;
	std::vector<int>							m_combi;
	NS_CORE TKValueArray						m_kValues;

public:
	TK() = delete;
	TK( double dK );

	const double							operator[]( size_t i ) const;
	bool									next();
};

NS_ARI_END