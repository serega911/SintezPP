#include "DefK.h"
#include "../Libraries/TSingletons.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

int main()
{
	NS_ARI DefK DK;

	if ( NS_CORE TSingletons::getInstance()->getSettings()->getDefKSettings()._doTest )
 		DK.calcExample();
	else
		DK.run();

	return 0;
}