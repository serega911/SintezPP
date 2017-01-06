#include "SchemeBuilderSwapPrev.h"

NS_ARI_USING


void ari::SchemeBuilderSwapPrev::run( IScheme_p & scheme, IPathBuildStartegy_p & strategy, const NS_CORE Code& code )
{
	scheme->clear();

	strategy->init( scheme->getWidth(), scheme->getHeight() );

	const auto& links = code.getCode();

	auto elem1 = links[0].getElem1();
	auto elem2 = links[0].getElem2();
	scheme->addLink( strategy->run( scheme->getAllElements(), elem1, elem2 ), links[0] );
}

ari::SchemeBuilderSwapPrev_p ari::SchemeBuilderSwapPrev::create()
{
	return SchemeBuilderSwapPrev_p( new SchemeBuilderSwapPrev );
}

ari::SchemeBuilderSwapPrev::SchemeBuilderSwapPrev()
{

}
