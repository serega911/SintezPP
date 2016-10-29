#include "LoaderFromFile.h"
#include "Singletons.h"

NS_CORE_USING

LoaderFromFile::LoaderFromFile()
{

}

LoaderFromFile* LoaderFromFile::getInstance()
{
	static core::LoaderFromFile loader;
	return &loader;
}

bool LoaderFromFile::load( std::vector<IIOItem*> & conteiners, const IOFileManager::eOutputFileType & file )
{
	for ( size_t i = 0; i < conteiners.size(); i++ )
	{
		if ( !core::Singletons::getInstance()->getIOFileManager()->loadFromFile( file, *conteiners[i] ) )
			return false;
	}
	return true;
}

