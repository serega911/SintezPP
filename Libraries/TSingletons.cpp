#include "TSingletons.h"


pss::TSingletons::TSingletons()
{
}

pss::TSingletons* pss::TSingletons::getInstance()
{
	static pss::TSingletons Singletons;
	return &Singletons;
}

pss::TSingletons::~TSingletons()
{
}

void pss::TSingletons::init()
{

}
