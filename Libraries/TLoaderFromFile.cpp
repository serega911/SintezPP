#include "TLoaderFromFile.h"
#include "TSingletons.h"

NS_CORE_USING

TLoaderFromFile::TLoaderFromFile()
{

}

TLoaderFromFile* TLoaderFromFile::getInstance()
{
	static core::TLoaderFromFile loader;
	return &loader;
}

bool TLoaderFromFile::load( std::vector<IIOItem*> & conteiners, const TIOFileManager::eOutputFileType & file )
{
	for ( size_t i = 0; i < conteiners.size(); i++ )
	{
		if ( !core::TSingletons::getInstance()->getIOFileManager()->loadFromFile( file, *conteiners[i] ) )
			return false;
	}
	return true;
}

