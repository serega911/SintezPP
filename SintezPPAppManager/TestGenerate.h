#pragma once

#include "../Libraries/GlobalDefines.h"

#include "TestBase.h"
#include "StartAppCommand.h"

NS_ARI_START

class TestGenerate : public TestBase
{
private:

	TestGenerate( const NS_CORE UIGeneralData& data );


	bool										compareFiles( std::fstream& ethalon, std::fstream& working );

public:

	static TestGenerate* create( const NS_CORE UIGeneralData& data );

	virtual bool start() override;

};

NS_ARI_END
