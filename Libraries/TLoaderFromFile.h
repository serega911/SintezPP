#pragma once

#include "IContainer.h"
#include "TIOFileManager.h"
#include "GlobalDefines.h"
#include <vector>


NS_CORE_START

	class TLoaderFromFile
	{
	private:
		TLoaderFromFile();
		TLoaderFromFile( const TLoaderFromFile& ) = delete;
		TLoaderFromFile&						operator=( TLoaderFromFile& ) = delete;
	public:
		static TLoaderFromFile*					getInstance();
		bool									load( std::vector<IContainer*> & conteiners, const TIOFileManager::eOutputFileType & file );
	};

NS_CORE_END