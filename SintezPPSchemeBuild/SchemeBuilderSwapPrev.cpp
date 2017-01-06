#include "SchemeBuilderSwapPrev.h"

NS_ARI_USING


void ari::SchemeBuilderSwapPrev::run( IScheme_p & scheme, IPathBuildStartegy_p & strategy, const NS_CORE Code& code )
{
	scheme->clear();

	

	const auto& links = code.getCode();

	for ( auto& it : links )
	{
		auto elem1 = it.getElem1();
		auto elem2 = it.getElem2();

		strategy->init( scheme->getWidth(), scheme->getHeight() );
		const auto link = strategy->run( scheme->getAllElements(), elem1, elem2 );

		if (link.size())
			scheme->addLink( link ,it );
	}
}

ari::SchemeBuilderSwapPrev_p ari::SchemeBuilderSwapPrev::create()
{
	return SchemeBuilderSwapPrev_p( new SchemeBuilderSwapPrev );
}

ari::SchemeBuilderSwapPrev::SchemeBuilderSwapPrev()
{

}
