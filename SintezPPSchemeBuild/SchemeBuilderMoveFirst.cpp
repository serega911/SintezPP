#include <vector>
#include <set>

#include "../Libraries/Singletons.h"

#include "SchemeBuilderMoveFirst.h"
#include "Display.h"
#include "TraceLinkCommand.h"
#include "TraceFrictionCommand.h"


NS_ARI_USING


bool ari::SchemeBuilderMoveFirst::run( IScheme_p & scheme, ITraceStrategy_p & strategy, const NS_CORE Code& code )
{
	std::vector<ICommand_p> commands;
	IDisplay_p display = Display::create();

	const auto& generalData = NS_CORE Singletons::getInstance()->getGeneralData();
	const int frictionsStartPos = generalData._numberOfLinks + 2;
	const int frictionsAfterLastPos = generalData._numberOfLinks + 2 + generalData._numberOfFrictions;

	commands.emplace_back( TraceLinkCommand::create( scheme, strategy, code.getIn() ) );
	commands.emplace_back( TraceLinkCommand::create( scheme, strategy, code.getOut() ) );
	for ( const auto& link : code.getLinks() )
		commands.emplace_back( TraceLinkCommand::create( scheme, strategy, link ) );
	for ( const auto& frict : code.getFrictions() )
		commands.emplace_back( TraceFrictionCommand::create( scheme, strategy, frict ) );
	for ( const auto& brake : code.getBrakes() )
		commands.emplace_back( TraceLinkCommand::create( scheme, strategy, brake ) );

	std::set<std::vector<ICommand_p>> processed;
	const auto size = commands.size();

	const auto compareWithInitial = [&]()
	{
		bool ret = processed.find( commands ) != processed.end();
		processed.insert( commands );
		return ret;
	};

	for ( size_t i = 0, swapCount = 0; i < size; i++ )
	{
		if ( i == 0 )
		{
			scheme->clear();
			//scheme->print( display, "Cleared" );
		}

		if ( commands[i]->execute() )
		{
			commands[i]->apply();
			//scheme->print( display, "Executed and applied" );
		}
		else if ( ( swapCount > 0 && compareWithInitial() ) || swapCount > 100 )
		{
			return false;
		}
		else
		{
			ICommand_p com = commands[i];
			commands.erase( commands.begin() + i );
			commands.insert( commands.begin(), com );

			swapCount++;
			i = -1;
		}

	}

	scheme->print( display, "Done" );
	code.print();
	NS_CORE Log::pause();

	return true;

}

ari::SchemeBuilderMoveFirst_p ari::SchemeBuilderMoveFirst::create()
{
	return SchemeBuilderMoveFirst_p( new SchemeBuilderMoveFirst );
}

ari::SchemeBuilderMoveFirst::SchemeBuilderMoveFirst()
{

}
