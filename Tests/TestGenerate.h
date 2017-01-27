#pragma once

#include "../Libraries/GlobalDefines.h"

#include "AppManagerBase.h"
#include "Command.h"

NS_ARI_START

class TestGenerate : public AppManagerBase
{
private:

	TestGenerate( const Data& data );

	
	bool										compareFiles( std::fstream& ethalon, std::fstream& working );

public:

	static TestGenerate* create( const Data& data );

	virtual bool start() override;

};

NS_ARI_END
