#include <iostream>
#include <fstream>
#include <vector>
#include "../Libraries/func_lib.h"				// RK: include block comments like "//libaries"
#include "../Libraries/TCode.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TSingletons.h"
#include "DefK.h"


#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

int main()
{
	NS_ARI DefK DK;
 	DK.run();

	return 0;
}