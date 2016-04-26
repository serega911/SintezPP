#pragma once

#include "../Libraries/IContainer.h"
#include "../Libraries/TIOFileManager.h"
#include <vector>
#include <vector>


namespace pss
{
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
}