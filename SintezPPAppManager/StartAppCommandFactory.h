#pragma once

#include <string>

#include "../Libraries/TestGlue.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/UIGeneralData.h"
#include "../Libraries/UISpecialData.h"

#include "StartAppCommand.h"

NS_ARI_START

class StartAppCommandFactory : public ICommand
{
public:

	static StartAppCommand_p					create( const std::string& appName );
	static StartAppCommand_p					create( const std::string& appName, const NS_CORE UIGeneralData& generalData );
	static StartAppCommand_p					create( const std::string& appName, const NS_CORE UIGeneralData& generalData, const NS_CORE UISpecialData& specialData );

};


NS_ARI_END