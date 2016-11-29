#include "../Libraries/Parser.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

NS_CORE_USING

int main()
{
	//auto settings = core::Singletons::getInstance()->getSettings();

	Log::log( "Black text", true, Log::BLACK );
	Log::log( "White text", true, Log::WHITE );
	Log::log( "Red text", true, Log::RED );
	Log::log( "Green text", true, Log::GREEN, Log::YELLOW );
	Log::log( "Blue text", true, Log::BLUE );
	Log::log( "Yellow text", true, Log::YELLOW );

	system("pause");

	return 0;
}