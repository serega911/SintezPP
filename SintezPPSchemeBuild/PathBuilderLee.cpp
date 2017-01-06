#include<set>

#include "Display.h"
#include "PathBuilderLee.h"

NS_ARI_USING

void ari::PathBuilderLee::init(  const size_t width, const size_t height )
{
	m_width = width + 2;
	m_height = height + 2;

	//resize field
	m_field.clear();
	m_field.resize( m_height );
	for ( auto & it : m_field )
		it.resize( m_width );

	//create borders
	for ( int i = 0; i < m_height; i++ )
	{
		m_field[i][0]._status = WALL;
		m_field[i][m_width - 1]._status = WALL;
	}
	for ( int j = 1; j < m_width - 1; j++ )
	{
		m_field[0][j]._status = WALL;
		m_field[m_height - 1][j]._status = WALL;
	}
}

std::vector<Cordinate> ari::PathBuilderLee::run( const std::vector<ISchemeElement_p>& elements, NS_CORE Element& start, NS_CORE Element& finish )
{
	fillField( elements, start, finish );
	
	spreadWave();

	return findPath();
}

ari::PathBuilderLee_p ari::PathBuilderLee::create()
{
	return PathBuilderLee_p( new PathBuilderLee );
}

ari::PathBuilderLee::PathBuilderLee()
{

}

void ari::PathBuilderLee::printField()
{
	system( "cls" );
	IDisplay_p disp = Display::create();

	for ( int i = 0; i < m_height; i++ )
	{
		for ( int j = 0; j < m_width; j++ )
		{
			switch ( m_field[i][j]._status )
			{
			case EMPTY:		disp->setColors(NS_CORE eColor::BLACK, NS_CORE eColor::WHITE); break;
			case START:		disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::YELLOW ); break;
			case FINISH:	disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::GREEN ); break;
			case WALL:		disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::RED ); break;
			case ADJOINED:		disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::BLUE ); break;
			}
			disp->print( Cordinate( j, i ), m_field[i][j]._value % 10 + '0' );
		}
	}

	disp->resetColors();
	disp->print( { 0, 20 }, '>' );
	system( "pause" );
}

bool ari::PathBuilderLee::verifyCord( const Cordinate& cord )
{
	return cord.m_x > 0 && cord.m_x < m_width - 1 && cord.m_y > 0 && cord.m_y < m_height - 1;
}

void ari::PathBuilderLee::fillField( const std::vector<ISchemeElement_p>& elements, NS_CORE Element& start, NS_CORE Element& finish )
{
	for ( const auto & element : elements )
	{
		const auto& cords = element->getCordsWorldSpace();

		for ( const auto & cord : cords )
		{
			eCellStatus status = WALL;

			if ( cord->isConsist( start ) )
				status = START;
			else if ( cord->isConsist( finish ) )
				status = FINISH;

			const Cordinate cordinate = cord->getCord() + Cordinate( 1, 1 );
			fieldAt( cordinate )._status = status;

			auto neighbors = cordinate.get8Neighbors();
			for ( const auto & it : neighbors )
			{
				if ( verifyCord( it ) && fieldAt( it )._status == EMPTY )
					fieldAt(it)._status = ADJOINED;
			}

		}
	}

	printField();
}

bool ari::PathBuilderLee::spreadWave()
{
	std::set<Cordinate> currentWave;
	std::set<Cordinate> nextWave;

	//заполн€ем текущую волну клетками финиша
	for ( size_t x = 1; x < m_width - 1; x++ )
	{
		for ( size_t y = 1; y < m_height - 1; y++ )
		{
			if ( m_field[y][x]._status == FINISH )
				currentWave.insert( Cordinate( x, y ) );
		}
	}

	//–аспространение волны
	int ni = 1;
	while ( currentWave.size() != 0 )
	{
		for ( auto& cord : currentWave )
		{
			auto neighbors = cord.getNeighbors();
			for ( const auto& neighbor : neighbors )
			{
				int value = fieldAt( cord )._value + 1;

				if ( (fieldAt( neighbor.second )._status == EMPTY || fieldAt( neighbor.second )._status == ADJOINED) && fieldAt(neighbor.second)._value == 0 )
				{
					fieldAt( neighbor.second )._value = value;
					nextWave.insert( neighbor.second );
				}
				else if ( fieldAt( neighbor.second )._status == START )
				{
					fieldAt( neighbor.second )._value = value;
					m_startCord = neighbor.second;
					return true;
				}
			}
		}

		currentWave = nextWave;
		nextWave.clear();

		printField();
		ni++;
	}
	return false;
}

PathBuilderLee::Cell& ari::PathBuilderLee::fieldAt( const Cordinate& cord )
{
	return m_field[cord.m_y][cord.m_x];
}

std::vector<Cordinate> ari::PathBuilderLee::findPath()
{
	// строим путь
	std::vector<Cordinate> path;
	Cordinate current = m_startCord;
	path.emplace_back( current );
	eDirection direction = eDirection::DOWN;

	while ( fieldAt(current)._status != FINISH )
	{
		auto neighbors = current.getNeighbors();

		Cordinate nextForward = neighbors.at( direction );
		auto min = fieldAt( nextForward )._value;

		Cordinate nextEmpty, nextAdjoined;
		int minEmpty = fieldAt( current )._value;
		int minAdjoined = fieldAt( current )._value;;
		eDirection emptyDirection;
		eDirection adjoinedDirection;

		for ( auto& neighbor : neighbors )
		{
			auto& cell = fieldAt( neighbor.second );

			if ( cell._status == FINISH )
			{
				current = neighbor.second;
				break;
			}
			else if ( cell._value != 0  )
			{
				if ( cell._status == EMPTY && cell._value < minEmpty )
				{
					emptyDirection = neighbor.first;
					minEmpty = cell._value;
					nextEmpty = neighbor.second;
				}
				else if ( cell._status == ADJOINED && cell._value < minAdjoined )
				{
					adjoinedDirection = neighbor.first;
					minAdjoined = cell._value;
					nextAdjoined = neighbor.second;
				}
			}
		}

		if ( fieldAt( current )._status != FINISH )
		{
			if ( minEmpty < fieldAt( current )._value && fieldAt( nextForward )._value != minEmpty )
			{
				direction = emptyDirection;
				current = nextEmpty;
			}
			else if( fieldAt( nextForward )._value != 0 && fieldAt( nextForward )._value < fieldAt( current )._value )
			{
				current = nextForward;
			}
			else 
			{
				direction = adjoinedDirection;
				current = nextAdjoined;
			}

		}

		/*
		auto next = neighbors.at( direction );
		if ( fieldAt( next )._value < fieldAt( current )._value && ( fieldAt( next )._value != 0 || fieldAt( next )._status == FINISH ) )
		{
			current = next;
		}

		auto min = fieldAt( current )._value;
		for ( auto& neighbor : neighbors )
		{
			if ( fieldAt( neighbor.second )._value < min && ( fieldAt( neighbor.second )._value != 0 || fieldAt( next )._status == FINISH ) )
			{
				min = fieldAt( neighbor.second )._value;
				current = neighbor.second;
				direction = neighbor.first;
			}
		}
		*/

		path.emplace_back( current );

		IDisplay_p disp = Display::create();
		disp->setColors( NS_CORE eColor::WHITE, NS_CORE eColor::BLACK );
		for ( const auto& it : path )
			disp->print( it, '#' );
		disp->resetColors();
		disp->print( { 0, 20 }, '>' );
		system( "pause" );
	}
	
	

	return path;
}

