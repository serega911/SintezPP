#pragma once
#include <vector>
#include <iostream>

#include "../Libraries/IIOItem.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/OrderedSample.h"

NS_ARI_START

class InternalGearRatios : public NS_CORE InternalGearRatios
{
private:
	bool										m_isFinded;
	NS_CORE OrderedSample<NS_CORE InternalGearRatioValueArray> m_combi;
	//std::vector<NS_CORE InternalGearRatioValue>	m_k;

public:
	InternalGearRatios() = delete;
	InternalGearRatios( const NS_CORE InternalGearRatioValueArray& k );
	InternalGearRatios( const NS_CORE InternalGearRatioValue dK );
	InternalGearRatios( NS_CORE InternalGearRatios& k );

	const NS_CORE InternalGearRatioValue		operator[]( size_t i ) const;
	bool										next();
};

NS_ARI_END