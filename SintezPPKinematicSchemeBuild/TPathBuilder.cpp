#include "TPathBuilder.h"
#include <set>
#include <iostream>


void pss::TPathBuilder::initField( const pss::TKinematicScheme & scheme, core::TLink link )
{
	m_field.resize( scheme.size() );
	for ( auto & it : m_field )
		it.resize( TPlanetaryGearSet::s_ySize );

	for ( auto x = 0; x < m_field.size(); x++ )
	{
		for ( auto y = 0; y < m_field[x].size(); y++ )
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

bool pss::TPathBuilder::spreadWave()
{
	std::set<pss::TCordinates> currentWave;
	std::set<pss::TCordinates> nextWave;

	//��������� ������� ����� �������� ������
	for ( int x = 0; x < m_field.size( ); x++ )
	{
		for ( int y = 0; y < m_field[x].size(); y++ )
		{
			if ( m_field[x][y] == m_finish )
				currentWave.insert( pss::TCordinates(x,y) );
		}
	}

	system( "cls" );
	printField();
	//system( "pause" );

	//��������������� �����
	int ni = 1;
	while ( currentWave.size() != 0 )
	{
		for ( auto& cord : currentWave )
		{
			auto neighbors = cord.getNeighbors();
			for ( auto& neighbor : neighbors )
			{
				if ( m_field[neighbor.second.m_x][neighbor.second.m_y] == m_empty )
				{
					m_field[neighbor.second.m_x][neighbor.second.m_y] = ni;
					nextWave.insert( neighbor.second );
				}
				else if ( m_field[neighbor.second.m_x][neighbor.second.m_y] == m_start )
				{
					return true;
				}
			}
		}
				system( "cls" );
				printField();
		currentWave = nextWave;
		nextWave.clear();
		ni++;
	}
	return false;
}

void pss::TPathBuilder::printField()
{
	for ( int x = 0; x < m_field.size(); x++ )
	{
		for ( int y = 0; y < m_field[x].size(); y++ )
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

pss::TPathBuilder::TPathBuilder()
{
}

std::vector<pss::TCordinates> pss::TPathBuilder::findPath()
{
	// ������ ����
	std::vector<pss::TCordinates> path;
	pss::TCordinates current = findStartCell();
	path.emplace_back( current );
	pss::eDirection direction = pss::eDirection::DOWN;

	

	while ( m_field[current.m_x][current.m_y] != m_finish)
	{
		m_field[current.m_x][current.m_y] = m_wall;
		auto neighbors = current.getNeighbors( );

		auto next = neighbors.at(direction);
		if ( m_field[next.m_x][next.m_y] < m_field[current.m_x][current.m_y] && m_field[next.m_x][next.m_y] != m_empty )
		{
			current = next;
		}

		for ( auto& neighbor : neighbors )
		{
			if ( m_field[neighbor.second.m_x][neighbor.second.m_y] < m_field[current.m_x][current.m_y] && m_field[neighbor.second.m_x][neighbor.second.m_y] != m_empty )
			{
				current = neighbor.second;
				direction = neighbor.first;
			}
		}

		
		path.emplace_back( current );
		system( "cls" );
		printField();
	}
	path.emplace_back( current );
	return path;
}

pss::TCordinates pss::TPathBuilder::findStartCell()
{
	// ���� ������ ������
	pss::TCordinates start( 0, 0 );
	int pathLenght = m_start;
	for ( int x = 1; x < m_field.size() - 1; x++ )
	{
		for ( int y = 1; y < m_field[x].size() - 1; y++ )
		{
			if ( m_field[x][y] == m_start )
			{
				pss::TCordinates cord( x, y );
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

std::vector<pss::TCordinates> pss::TPathBuilder::findPath( const pss::TKinematicScheme & scheme, core::TLink link )
{
	int maxX = scheme.size();
	int maxY = TPlanetaryGearSet::s_ySize;
	m_start = maxX * maxY;
	m_finish = 0;
	m_empty = maxX * maxY + 1;
	m_wall = maxX * maxY + 2;
	initField( scheme, link );
	if ( spreadWave() )
	{
		return findPath();

	}
	return{};
}
