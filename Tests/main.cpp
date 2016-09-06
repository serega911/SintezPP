#include "../Libraries/TSingletons.h"

#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

int main()
{
	NS_CORE TCombinatoricsValueArray mas;
	bool result;
	result = NS_CORE TSingletons::getInstance()->getCombinatorics()->getPremutation( 3, 1, mas );
	result = NS_CORE TSingletons::getInstance()->getCombinatorics()->getPremutation( 3, 6, mas );

	result = NS_CORE TSingletons::getInstance()->getCombinatorics()->getPremutation( 4, 1, mas );
	result = NS_CORE TSingletons::getInstance()->getCombinatorics()->getPremutation( 4, 6, mas );

	result = NS_CORE TSingletons::getInstance()->getCombinatorics()->getOrderedSample( 20, 2, 5, mas );
	result = NS_CORE TSingletons::getInstance()->getCombinatorics()->getOrderedSample( 20, 2, 400, mas );

	return 0;
}