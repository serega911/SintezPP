
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TestGenerate.h"
#include "../Libraries/UISpecialData.h"
#include "StartAppCommandFactory.h"

NS_ARI_USING

bool ari::TestGenerate::start()
{
	const std::string fileName = "done.pkp";
	std::string ethalonFilePath = getEthalonFolderPath() + fileName;
	std::string workingFilePath = getWorkingFolderPath() + fileName;

	remove( workingFilePath.c_str() );

	StartAppCommand_p command = StartAppCommandFactory::create( "SintezPPGenerate.exe", getGeneralData() );
	command->execute();

	std::fstream ethalonFile;
	std::fstream workingFile;

	ethalonFile.open( ethalonFilePath, std::ofstream::in );
	workingFile.open( workingFilePath, std::ofstream::in );

	bool res = compareFiles( ethalonFile, workingFile );

	ethalonFile.close();
	workingFile.close();

	return res;
}

TestGenerate* ari::TestGenerate::create( const  NS_CORE UIGeneralData& data )
{
	TestGenerate* ret = new TestGenerate( data );
	return ret;
}

ari::TestGenerate::TestGenerate( const  NS_CORE UIGeneralData& data )
	: TestBase( data )
{

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

