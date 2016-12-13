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
	for ( const auto& it: conteiners )
	{
		if ( !core::Singletons::getInstance()->getIOFileManager()->loadFromFile( file, *it ) )
			return false;
	}
	return true;
}

