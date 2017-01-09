#include "SchemeBuilderSwapPrev.h"
#include "Display.h"

NS_ARI_USING


bool ari::SchemeBuilderSwapPrev::run( IScheme_p & scheme, IPathBuildStartegy_p & strategy, const NS_CORE Code& code )
{
	int count = 0;
	auto links = code.getCode();
	const int size = links.size();

l:	scheme->clear();

	for ( int i = 0; i < size; i++ )
	{
		auto elem1 = links[i].getElem1();
		auto elem2 = links[i].getElem2();

		strategy->init( scheme->getWidth(), scheme->getHeight() );
		const auto link = strategy->run( scheme->getAllElements(), elem1, elem2 );

		if ( link.size() )
		{
			scheme->addLink( link, links[i] );
		}
		else if (i > 0)
		{
			
			std::swap( links[i], links[i - 1] );
			if ( count > 10 )
				return false;

			count++;
			goto l;
		}
		else
		{
			return false;
		}
	}

	scheme->print( Display::create() );

	return true;
}

ari::SchemeBuilderSwapPrev_p ari::SchemeBuilderSwapPrev::create()
{
	return SchemeBuilderSwapPrev_p( new SchemeBuilderSwapPrev );
}

ari::SchemeBuilderSwapPrev::SchemeBuilderSwapPrev()
{

}
