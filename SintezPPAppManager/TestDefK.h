#pragma once

#include "../Libraries/GlobalDefines.h"

#include "TestBase.h"
#include "StartAppCommand.h"

NS_ARI_START

class TestDefK : public TestBase
{
private:

	TestDefK( const NS_CORE UIGeneralData& data );

public:

	static TestDefK* create( const NS_CORE UIGeneralData& data );

	virtual bool start() override;

};

NS_ARI_END