#pragma once
#include "../Libraries/GearBoxWithChanger.h"

NS_ARI_START

class GearBoxWithChangerSpecialFrictionProcess :
	public NS_CORE GearBoxWithChanger
{
public:

	GearBoxWithChangerSpecialFrictionProcess( const NS_CORE Code& code );

	virtual NS_CORE MultiLinkArray					getChainsForCurrentGear() const override;

};

NS_ARI_END