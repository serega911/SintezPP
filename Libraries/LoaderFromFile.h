#pragma once

#include "IIOItem.h"
#include "IOFileManager.h"
#include "GlobalDefines.h"
#include <vector>


NS_CORE_START

class LoaderFromFile
{
private:

	LoaderFromFile();
	LoaderFromFile( const LoaderFromFile& ) = delete;

	LoaderFromFile&								operator=( LoaderFromFile& ) = delete;

public:

	static LoaderFromFile*						getInstance();
	bool										load( std::vector<IIOItem*> & conteiners, const IOFileManager::eOutputFileType & file );

};

NS_CORE_END