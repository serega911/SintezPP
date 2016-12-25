
#include <vector>
#include "TestGenerate.h"
#include "TestDefK.h"


#pragma comment(lib, "../Libraries/SintezPPLibary.lib")




int main()
{
	std::vector<NS_ARI TestBase*> tests;

	tests.push_back( NS_ARI TestGenerate::create( { 2, 2, 2 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 2, 3, 3 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 2, 3 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 2, 4 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 3, 5 } ) );
	/*
	tests.push_back( NS_ARI TestDefK::create( { 2, 2, 2 } ) );
	tests.push_back( NS_ARI TestDefK::create( { 2, 3, 3 } ) );
	tests.push_back( NS_ARI TestDefK::create( { 3, 2, 3 } ) );
	tests.push_back( NS_ARI TestDefK::create( { 3, 2, 4 } ) );
	tests.push_back( NS_ARI TestDefK::create( { 3, 3, 5 } ) );
	*/



	for ( auto& it : tests )
		it->start();

	for ( auto& it : tests )
		delete it;

	system("pause");
}