#include <iostream>


#pragma comment(lib, "../Libraries/SintezPPLibary.lib")


int main()
{
	int resp = system( "SintezPPGenerate.exe" );

	std::cout << "resp = " << resp << std::endl;

	system("pause");
}