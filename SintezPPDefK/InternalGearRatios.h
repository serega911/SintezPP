#pragma once
#include <vector>
#include <iostream>

#include "../Libraries/IIOItem.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/CombinatoricsValueArray.h"

NS_ARI_START

class InternalGearRatios : public NS_CORE InternalGearRatios
{
private:
	bool										m_isFinded;
	NS_CORE InternalGearRatioValue				m_dK;
	NS_CORE CombinatoricsValueArray				m_combi;
	NS_CORE InternalGearRatioValueArray			m_kValues;
	size_t										m_currentOrderedSample;

public:
	InternalGearRatios() = delete;
	InternalGearRatios( NS_CORE InternalGearRatioValue dK );
	InternalGearRatios( NS_CORE InternalGearRatios& k );

	const NS_CORE InternalGearRatioValue		operator[]( size_t i ) const;
	bool										next();
};

NS_ARI_END