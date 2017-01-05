#include "PathBuilderLee.h"

NS_ARI_USING

void ari::PathBuilderLee::init( const std::vector<ISchemeElement_p>& elements )
{

}

std::vector<Cordinate> ari::PathBuilderLee::run( NS_CORE Element& start, NS_CORE Element& finish )
{
	return{};
}

ari::PathBuilderLee_p ari::PathBuilderLee::create()
{
	return PathBuilderLee_p( new PathBuilderLee );
}

ari::PathBuilderLee::PathBuilderLee()
{

}

