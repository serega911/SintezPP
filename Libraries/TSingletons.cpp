#include "TSingletons.h"


pss::TSingletons::TSingletons()
{
	init();
}

pss::TSingletons* pss::TSingletons::getInstance()
{
	static pss::TSingletons Singletons;
	return &Singletons;
}

pss::TSingletons::~TSingletons()
{
}

pss::TIOFileManager* pss::TSingletons::getIOFileManager()
{
	return pss::TIOFileManager::getInstance();
}

void pss::TSingletons::init()
{
	getIOFileManager()->init();
}