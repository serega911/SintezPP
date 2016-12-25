#pragma once

#include "../Libraries/GlobalDefines.h"

#include "TestBase.h"
#include "Command.h"

NS_ARI_START

class TestDefK : public TestBase
{
private:

	TestDefK( const Data& data );

	Command										createCommand( const std::vector<std::pair<float, float>> & ranges, const std::vector<float> & ratios );

public:

	static TestDefK* create( const Data& data );

	virtual bool start() override;

};

NS_ARI_END