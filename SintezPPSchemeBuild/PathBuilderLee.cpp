#include<set>

#include "Display.h"
#include "PathBuilderLee.h"

NS_ARI_USING

ari::PathBuilderLee::PathBuilderLee()
{
}

ari::PathBuilderLee_p ari::PathBuilderLee::create()
{
	return PathBuilderLee_p( new PathBuilderLee );
}

void ari::PathBuilderLee::init(  const size_t width, const size_t height )
{
	m_width = width;
	m_height = height;

	//resize field
	m_field.clear();

	//create borders
	for ( int y = -1; y <= m_height; y++ )
	{
		fieldAt( Cordinate( -1, y ) )._status = WALL;
		fieldAt( Cordinate(m_width, y ) )._status = WALL;
	}
	for ( int x = 0; x < m_width; x++ )
	{
		fieldAt( Cordinate( x, -1 ) )._status = WALL;
		fieldAt( Cordinate( x, m_height ) )._status = WALL;
	}
}

std::vector<Cordinate> ari::PathBuilderLee::run( const std::vector<ISchemeElement_p>& elements, NS_CORE Element& start, NS_CORE Element& finish )
{
	std::vector<Cordinate> ret;

	fillField( elements, start, finish );
	//printField();
	if ( spreadWave() )
	{
		//printField();
		ret = findPath();
	}

	return ret;
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

			const Cordinate& cordinate = cord->getCord();

			fieldAt( cordinate )._status = status;

			auto neighbors = cordinate.get8Neighbors();
			for ( const auto & it : neighbors )
			{
				if ( verifyCord( it ) && fieldAt( it )._status == EMPTY )
					fieldAt(it)._status = ADJOINED;
			}

		}
	}
}

bool ari::PathBuilderLee::spreadWave()
{
	std::set<Cordinate> currentWave;
	std::set<Cordinate> nextWave;

	//заполн€ем текущую волну клетками финиша
	for ( const auto& it : m_field )
	{
		if ( it.second._status == FINISH )
			currentWave.insert( it.first );
	}

	//–аспространение волны
	bool achieved = false;
	bool terminate = false;
	while ( currentWave.size() != 0 && !terminate )
	{
		terminate = achieved;
		for ( auto& cord : currentWave )
		{
			PathBuilderLee::Cell& cordCell = fieldAt( cord );

			if ( achieved && cordCell._value < fieldAt( m_startCord )._value )
				terminate = false;

			auto neighbors = cord.getNeighbors();
			for ( const auto& neighbor : neighbors )
			{
				PathBuilderLee::Cell& neighborCell = fieldAt( neighbor.second );

				int value = cordCell._value + (neighborCell._status == ADJOINED ? 5 : 1);

				if ( neighborCell._status == START && canIFill( fieldAt( m_startCord ), value ) )
				{
					neighborCell._value = value;
					m_startCord = neighbor.second;
					achieved = true;
				}
				else if ( ( neighborCell._status == EMPTY || neighborCell._status == ADJOINED ) && canIFill( neighborCell, value ) )
				{
					neighborCell._value = value;
					//printField();
					nextWave.insert( neighbor.second );
				}			
			}
		}

		currentWave = nextWave;
		nextWave.clear();
	}

	return terminate;
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

		auto next = neighbors.at( direction );
		if ( fieldAt( next )._value != 0 && fieldAt( next )._value < fieldAt( current )._value )
		{
			current = next;
		}

		auto min = fieldAt( current )._value;
		for ( auto& neighbor : neighbors )
		{
			if ( fieldAt( neighbor.second )._status == eCellStatus::FINISH )
			{
				current = neighbor.second;
				break;
			}
			else if ( fieldAt( neighbor.second )._value != 0 && fieldAt( neighbor.second )._value < min )
			{
				min = fieldAt( neighbor.second )._value;
				current = neighbor.second;
				direction = neighbor.first;
			}
		}

		path.emplace_back( current );
		//printRoute( path );
	}
	
	return path;
}

bool ari::PathBuilderLee::verifyCord( const Cordinate& cord )
{
	return cord.m_x >= 0 && cord.m_x < m_width && cord.m_y >= 0 && cord.m_y < m_height;
}

bool ari::PathBuilderLee::canIFill( const Cell& cord, const int value )
{
	return cord._value == 0 || value < cord._value;
}

PathBuilderLee::Cell& ari::PathBuilderLee::fieldAt( const Cordinate& cord )
{
	return m_field[cord];
}

void ari::PathBuilderLee::printField()
{
	system( "cls" );
	IDisplay_p disp = Display::create();

	for ( const auto& it : m_field )
	{
		switch ( it.second._status )
		{
		case EMPTY:		disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::WHITE ); break;
		case START:		disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::YELLOW ); break;
		case FINISH:	disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::GREEN ); break;
		case WALL:		disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::RED ); break;
		case ADJOINED:	disp->setColors( NS_CORE eColor::BLACK, NS_CORE eColor::LIGHT_BLUE ); break;
		}
		disp->print( it.first + Cordinate( 1, 1 ), it.second._value % 10 + '0' );
	}

	disp->resetColors();
	disp->print( { 0, 20 }, '>' );
	system( "pause" );
}

void ari::PathBuilderLee::printRoute( const std::vector<Cordinate> & route )
{
	IDisplay_p disp = Display::create();
	disp->setColors( NS_CORE eColor::WHITE, NS_CORE eColor::BLACK );
	for ( const auto& it : route )
		disp->print( it + Cordinate(1,1), '#' );
	disp->resetColors();
	disp->print( { 0, 20 }, '>' );
	system( "pause" );
}

