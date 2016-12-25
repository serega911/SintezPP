
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TestGenerate.h"

NS_ARI_USING

bool ari::TestGenerate::start()
{
	const std::string fileName = "done.pkp";
	std::string ethalonFilePath = getEthalonFolderPath() + fileName;
	std::string workingFilePath = getWorkingFolderPath() + fileName;

	remove( workingFilePath.c_str() );

	Command command = createCommand();
	system( command.get().c_str() );

	std::fstream ethalonFile;
	std::fstream workingFile;

	ethalonFile.open( ethalonFilePath, std::ofstream::in );
	workingFile.open( workingFilePath, std::ofstream::in );

	bool res = compareFiles( ethalonFile, workingFile );

	ethalonFile.close();
	workingFile.close();
	
	return res;
}

TestGenerate* ari::TestGenerate::create( const Data& data )
{
	TestGenerate* ret = new TestGenerate( data );
	return ret;
}

ari::TestGenerate::TestGenerate( const Data& data )
	: TestBase(data)
{

}

ari::Command ari::TestGenerate::createCommand()
{
	Command command( "SintezPPGenerate.exe" );
	command.addParam( wKey, std::to_string( getW() ) );
	command.addParam( nKey, std::to_string( getN() ) );
	command.addParam( dKey, std::to_string( getD() ) );

	return command;
}

bool ari::TestGenerate::compareFiles( std::fstream& ethalon, std::fstream& working )
{
	while ( !working.eof() && !ethalon.eof() )
	{
		std::string str1;
		std::string str2;

		getline( working, str1 );
		getline( ethalon, str2 );

		if ( str1 != str2 )
		{
			std::cout << str1 << " : " << str2 << std::endl;
			return false;
		}
	}

	return true;
}

