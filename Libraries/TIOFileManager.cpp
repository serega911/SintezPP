#include "../Libraries/TIOFileManager.h"

pss::TIOFileManager::TIOFileManager()
{
}

pss::TIOFileManager* pss::TIOFileManager::getInstance()
{
	pss::TIOFileManager ioFileManager;
	return &ioFileManager;
}

pss::TIOFileManager::~TIOFileManager()
{
}