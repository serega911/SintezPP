#pragma once

#include "../Libraries/GlobalDefines.h"

#include "TestBase.h"
#include "Command.h"

NS_ARI_START

class TestGenerate : public TestBase
{
private:

	TestGenerate( const Data& data );

	Command										createCommand();
	bool										compareFiles( std::fstream& ethalon, std::fstream& working );

public:

	static TestGenerate* create( const Data& data );

	virtual bool start() override;

};

NS_ARI_END
