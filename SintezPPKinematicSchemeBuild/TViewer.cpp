#include "TViewer.h"
#include "../Libraries/TGearBox.h"
#include "../Libraries/func_lib.h"


NS_ARI_USING

const int ari::TViewer::s_colors[] = { WHITE, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE };

void ari::TViewer::printKinematicScheme( const TKinematicScheme& scheme )
{
	NS_CORE TGearBox gearBox( scheme.m_code );
	gearBox.createChains();
	const auto& chains = gearBox.getChains();

	for ( int row = scheme[0].size()-1; row >= 0; row-- )
	{
		for ( auto col = 0; col < scheme.size(); col++ )
		{
			if ( scheme[col][row].size() != 0 )
			{
				int currColorPos = 0;
				for ( int color = 0; color < chains.size(); color++ )
				{
					if ( chains[color].intersect( scheme[col][row] ) )
					{
						currColorPos = color+1;
						break;
					}
				}

				core::SetColor( s_colors[currColorPos], 0 );
				std::cout << '#';
			}
			else
				std::cout << ' ';

		}
		std::cout << std::endl;
	}
}



