#pragma once
#include <vector>
#include <iostream>

#include "../Libraries/IContainer.h"
#include "../Libraries/TK.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TCombinatoricsValueArray.h"

NS_ARI_START

class TK : public NS_CORE TK
{
private:
	bool										m_isFinded;
	NS_CORE TKValue								m_dK;
	NS_CORE TCombinatoricsValueArray			m_combi;
	NS_CORE TKValueArray						m_kValues;
	size_t										m_currentOrderedSample;

public:
	TK() = delete;
	TK( NS_CORE TKValue dK );
	TK( NS_CORE TK& k );

	const NS_CORE TKValue						operator[]( size_t i ) const;
	bool										next();
};

NS_ARI_END