
#include <vector>
#include "TestGenerate.h"
#include "TestBase.h"


#pragma comment(lib, "../Libraries/SintezPPLibary.lib")

bool defKTest( size_t w, size_t n, size_t d, const std::vector<std::pair<float, float>> & ranges, const std::vector<float> & ratios )
{
	/*

	std::string command = "SintezPPDefK.exe";
	addParam( command, wKey, std::to_string( w ) );
	addParam( command, nKey, std::to_string( n ) );
	addParam( command, dKey, std::to_string( d ) );

	for ( int i = 0; i < ranges.size(); i++ )
	{
		addParam( command, rangeBeginKey, std::to_string( ranges[i].first ) );
		addParam( command, rangeEndKey, std::to_string( ranges[i].second ) );
	}

	for ( int i = 0; i < ratios.size(); i++ )
	{
		addParam( command, iKey, std::to_string( ratios[i] ) );
	}

	system( command.c_str() );
*/
}



int main()
{
	std::vector<NS_ARI TestBase*> tests;

	tests.push_back( NS_ARI TestGenerate::create( { 2, 2, 2 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 2, 3, 3 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 2, 3 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 2, 4 } ) );
	tests.push_back( NS_ARI TestGenerate::create( { 3, 3, 5 } ) );



	//defKTest( 2, 2, 2, { { -5, -2 }, { 2, 5 } }, { 2, 3 } );


	for ( auto& it : tests )
		it->start();

	for ( auto& it : tests )
		delete it;

	system("pause");
}