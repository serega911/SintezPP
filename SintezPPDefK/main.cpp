#include "DefK.h"
#include "../Libraries/Singletons.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

int main()
{
	NS_ARI DefK DK;

	if ( NS_CORE Singletons::getInstance()->getSettings()->getDefKSettings()._doTest )
 		DK.calcExample();
	else
		DK.run();

	return 0;
}