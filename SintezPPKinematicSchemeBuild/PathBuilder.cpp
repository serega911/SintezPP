#include "PathBuilder.h"
#include <set>
#include <iostream>

NS_ARI_USING

void PathBuilder::initField( const KinematicScheme & scheme, core::Link link )
{
	m_field.resize( scheme.size() );
	for ( auto & it : m_field )
		it.resize( PlanetaryGearSet::s_ySize );

	for ( size_t x = 0; x < m_field.size(); x++ )
	{
		for ( size_t y = 0; y < m_field[x].size(); y++ )
		{
			// empty
			if ( scheme[x][y].size() == 0 )
			{
				m_field[x][y] = m_empty;
			}
			// start
			else if( scheme[x][y].find( link.getElem1( ) ) )
			{
				m_field[x][y] = m_start;
			}
			// finish
			else if ( scheme[x][y].find( NS_CORE Element::BRAKE ) && scheme[x][y].size() > 1 )
			{
				m_field[x][y] = m_wall;
			}
			else if ( scheme[x][y].find( link.getElem2() ) )
			{
				m_field[x][y] = m_finish;
			}
			// wall
			else
			{
				m_field[x][y] = m_wall;
			}
		}
	}
}

bool PathBuilder::spreadWave()
{
	std::set<Cordinate> currentWave;
	std::set<Cordinate> nextWave;

	//заполн€ем текущую волну клетками финиша
	for ( size_t x = 0; x < m_field.size(); x++ )
	{
		for ( size_t y = 0; y < m_field[x].size(); y++ )
		{
			if ( m_field[x][y] == m_finish )
				currentWave.insert( Cordinate(x,y) );
		}
	}

	//system( "cls" );
	//printField();
	//system( "pause" );

	//–аспространение волны
	int ni = 1;
	while ( currentWave.size() != 0 )
	{
		for ( auto& cord : currentWave )
		{
			auto neighbors = cord.getNeighbors();
			for ( auto& neighbor : neighbors )
			{
				int value = m_field[cord.m_x][cord.m_y] + 1;

				if ( m_field[neighbor.second.m_x][neighbor.second.m_y] == m_empty )
				{
					m_field[neighbor.second.m_x][neighbor.second.m_y] = value;				
					nextWave.insert( neighbor.second );
				}

				else if ( m_field[neighbor.second.m_x][neighbor.second.m_y] == m_start )
				{
					return true;
				}
			}
			//system( "pause" );
		}
		
		currentWave = nextWave;	
		nextWave.clear();

		//system( "cls" );
		//printField();
		ni++;
	}
	return false;
}

void PathBuilder::printField()
{
	for ( size_t x = 0; x < m_field.size(); x++ )
	{
		for ( size_t y = 0; y < m_field[x].size(); y++ )
		{
			if ( m_field[x][y] == m_start )
				std::cout << 's';
			else if ( m_field[x][y] == m_finish )
				std::cout << 'f';
			else if ( m_field[x][y] == m_empty )
				std::cout << ' ';
			else if ( m_field[x][y] == m_wall )
				std::cout << 'w';
			else
				std::cout << '.';

		}
		std::cout << std::endl;
	}
}

void ari::PathBuilder::addRestrictions()
{
	for ( int i = 1; i < m_field.size() - 1; i++ )
	{
		for ( int j = 0; j < m_field[i].size() - 1; j++ )
		{
			if (m_field[i][j] != m_wall && 
				m_field[i][j] != m_start &&
				m_field[i][j] != m_finish &&
				checkIsNear( Cordinate( i, j ), m_wall ) && 
				!checkIsNear( Cordinate( i, j ), m_start ) && 
				!checkIsNear( Cordinate( i, j ), m_finish ))
			{
				m_field[i][j] = m_start - 1;
			}
		}
	}
}

bool ari::PathBuilder::checkIsNear( const Cordinate& cord, const int elem )
 {
	auto neighbours = cord.getNeighbors();
	for ( const auto &neighbour : neighbours )
	{
		if ( m_field[neighbour.second.m_x][neighbour.second.m_y] == elem )
			return true;
	}
	return false;
 }

PathBuilder::PathBuilder()
{

}

TCordinatesArray PathBuilder::findPath()
{
	// строим путь
	TCordinatesArray path;
	Cordinate current = findStartCell();
	path.emplace_back( current );
	eDirection direction = eDirection::DOWN;

	

	while ( m_field[current.m_x][current.m_y] != m_finish)
	{
		m_field[current.m_x][current.m_y] = m_wall;
		auto neighbors = current.getNeighbors( );

		auto next = neighbors.at(direction);
		if ( m_field[next.m_x][next.m_y] < m_field[current.m_x][current.m_y] && m_field[next.m_x][next.m_y] != m_empty )
		{
			current = next;
		}

		auto min = m_field[current.m_x][current.m_y];
		for ( auto& neighbor : neighbors )
		{
			if ( m_field[neighbor.second.m_x][neighbor.second.m_y] < min && m_field[neighbor.second.m_x][neighbor.second.m_y] != m_empty )
			{
				min = m_field[neighbor.second.m_x][neighbor.second.m_y];
				current = neighbor.second;
				direction = neighbor.first;
			}
		}

		
		path.emplace_back( current );
		//system( "cls" );
		//printField();
	}
	path.emplace_back( current );
	return path;
}

Cordinate PathBuilder::findStartCell()
{
	// ищем клетку старта
	Cordinate start( 0, 0 );
	int pathLenght = m_start;
	for ( size_t x = 1; x < m_field.size() - 1; x++ )
	{
		for ( size_t y = 1; y < m_field[x].size() - 1; y++ )
		{
			if ( m_field[x][y] == m_start )
			{
				Cordinate cord( x, y );
				auto neighbors = cord.getNeighbors();
				for ( auto& neighbor : neighbors )
				{
					if ( m_field[neighbor.second.m_x][neighbor.second.m_y] < pathLenght )
					{
						start = cord;
						pathLenght = m_field[neighbor.second.m_x][neighbor.second.m_y];
					}
				}
			}
		}
	}
	return start;
}

TCordinatesArray PathBuilder::findPath( const KinematicScheme & scheme, core::Link link )
{
	int maxX = scheme.size();
	int maxY = PlanetaryGearSet::s_ySize;
	m_start = maxX * maxY;
	m_finish = 0;
	m_empty = maxX * maxY + 1;
	m_wall = maxX * maxY + 2;
	initField( scheme, link );
	addRestrictions();
	if ( spreadWave() )
	{
		return findPath();
	}
	else
	{
		initField( scheme, link );
		if ( spreadWave() )
		{
			return findPath();
		}
	}
	return{};
}
