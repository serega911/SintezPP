#include "../Libraries/TIOFileManager.h"

pss::TIOFileManager::TIOFileManager()
{
}

pss::TIOFileManager* pss::TIOFileManager::getInstance()
{
	static pss::TIOFileManager ioFileManager;
	return &ioFileManager;
}

pss::TIOFileManager::~TIOFileManager()
{
}

void pss::TIOFileManager::init()
{

}
