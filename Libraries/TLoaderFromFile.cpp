#include "TLoaderFromFile.h"
#include "TSingletons.h"

pss::TLoaderFromFile::TLoaderFromFile()
{

}

pss::TLoaderFromFile* pss::TLoaderFromFile::getInstance( )
{
	static pss::TLoaderFromFile loader;
	return &loader;
}

bool pss::TLoaderFromFile::load( std::vector<IContainer*> & conteiners, const TIOFileManager::eOutputFileType & file )
{
	for ( int i = 0; i < conteiners.size(); i++ )
	{
		if ( !pss::TSingletons::getInstance()->getIOFileManager()->loadFromFile( file, *conteiners[i] ) )
			return false;
	}
	return true;
}

