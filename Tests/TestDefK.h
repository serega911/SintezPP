#pragma once

#include "../Libraries/GlobalDefines.h"

#include "AppManagerBase.h"
#include "Command.h"

NS_ARI_START

class TestDefK : public AppManagerBase
{
private:

	TestDefK( const Data& data );

public:

	static TestDefK* create( const Data& data );

	virtual bool start() override;

};

NS_ARI_END