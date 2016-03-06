#include "../Libraries/TIOFileManager.h"

const std::string						pss::TIOFileManager::s_folder = "../results";

std::string pss::TIOFileManager::getFolder()
{
	return s_folder;
}

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
