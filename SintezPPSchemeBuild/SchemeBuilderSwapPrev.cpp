#include <vector>

#include "SchemeBuilderSwapPrev.h"
#include "Display.h"
#include "TraceLinkCommand.h"


NS_ARI_USING


bool ari::SchemeBuilderSwapPrev::run( IScheme_p & scheme, ITraceStrategy_p & strategy, const NS_CORE Code& code )
{
	const auto& links = code.getCode();
	const int size = links.size();
	std::vector<ICommand_p> commands;
	commands.reserve( size );
	IDisplay_p display = Display::create();

	int curr = -1;
	int lastFailPos = -1;

	for ( const auto& it : links )
	{
		commands.emplace_back( TraceLinkCommand::create( scheme, strategy, it ) );
	}

	for ( int i = 0, swapCount = 0; i < size; i++ )
	{
		if ( i == 0 )
		{
			scheme->clear();
			//scheme->print( display, "Cleared" );
		}

		if ( commands[i]->isApplied() && i < curr )
		{
			commands[i]->apply();
			//scheme->print( display, "Applied" );
		}
		else if ( commands[i]->execute() )
		{
			commands[i]->apply();
			//scheme->print( display, "Executed and applied" );
		}
		else if ( i == lastFailPos || swapCount > 100 )
		{
			return false;
		}
		else
		{
			lastFailPos = i;
			swapCount++;
			curr = i - 1;
			std::swap( commands[i], commands[curr] );
			i = -1;
		}

	}

	scheme->print( display, "Done" );

	return true;
	
}

ari::SchemeBuilderSwapPrev_p ari::SchemeBuilderSwapPrev::create()
{
	return SchemeBuilderSwapPrev_p( new SchemeBuilderSwapPrev );
}

ari::SchemeBuilderSwapPrev::SchemeBuilderSwapPrev()
{

}
