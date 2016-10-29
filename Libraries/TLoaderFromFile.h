#pragma once

#include "IIOItem.h"
#include "TIOFileManager.h"
#include "GlobalDefines.h"
#include <vector>


NS_CORE_START

class TLoaderFromFile
{
private:

	TLoaderFromFile();
	TLoaderFromFile( const TLoaderFromFile& ) = delete;

	TLoaderFromFile&							operator=( TLoaderFromFile& ) = delete;

public:

	static TLoaderFromFile*						getInstance();
	bool										load( std::vector<IIOItem*> & conteiners, const TIOFileManager::eOutputFileType & file );
	
};

NS_CORE_END