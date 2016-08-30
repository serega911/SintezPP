#include "TViewer.h"
#include "../Libraries/TGearBox.h"
#include "../Libraries/func_lib.h"
#include <algorithm>

NS_ARI_USING

const int ari::TViewer::s_colors[] = { WHITE, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE };

bool isChainsEqual( const NS_CORE TChain& ch1, const NS_CORE TChain& ch2 )
{
	auto chains1 = ch1.getElements();
	auto chains2 = ch2.getElements();

	if ( ch1.size() == ch2.size() )
	{
		for ( const auto& el1 : chains1 )
		{
			bool notFinded = true;
			for ( const auto& el2 : chains2 )
			{
				if ( el1 == el2 )
				{
					notFinded = false;
				}
			}
			if ( notFinded )
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void ari::TViewer::printKinematicScheme( const TKinematicScheme& scheme )
{
	NS_CORE TGearBox gearBox( scheme.m_code );
	gearBox.createChains();
	const auto& chains = gearBox.getChains();

	for ( int row = scheme[0].size()-1; row >= 0; row-- )
	{
		for ( size_t col = 0; col < scheme.size(); col++ )
		{
			if ( scheme[col][row].size() != 0 )
			{
				int currColorPos = 0;
				if ( scheme[col][row].find( NS_CORE TElement::BRAKE ) )
					currColorPos = 1;
				else
				{
					for ( size_t color = 0; color < chains.size(); color++ )
					{
						if ( isChainsEqual( chains[color], scheme[col][row] ) )
						{
							currColorPos = color + 2;
							break;
						}
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



