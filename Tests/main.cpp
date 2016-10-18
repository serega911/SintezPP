#include "../Libraries/TParser.h"
#include "../Libraries/TSingletons.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

int main()
{
	auto settings = core::TSingletons::getInstance()->getSettings();

	return 0;
}