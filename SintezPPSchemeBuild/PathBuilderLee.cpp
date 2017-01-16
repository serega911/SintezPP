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

	spreadWave( std::bind( &PathBuilderLee::prepareWave, this, std::placeholders::_1 ), std::bind( &PathBuilderLee::processWaveCell, this, std::placeholders::_1, std::placeholders::_2 ) );
	if ( fieldAt( m_startCord )._value != 0 )
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

			fieldAt( cord->getCord() )._status = status;

		}
	}

	int maxCost = 0;

	const auto prepareFunc = [&](Wave& wave)
	{
		for ( const auto& it : m_field )
		{
			if ( it.second._status != EMPTY )
				wave.insert( it.first );
		}
	};


	const auto processFunc = [&]( const Cordinate& waveCell, const Cordinate& neighbor )
	{
		bool isNeedToAdd = false;
		if ( verifyCord( neighbor ) )
		{
			Cell& neighborCell = fieldAt( neighbor );
			if ( neighborCell._status == EMPTY && neighborCell._cost == 1 )
			{
				maxCost = neighborCell._cost = fieldAt( waveCell )._cost + 4;
				isNeedToAdd = true;
			}
		}
		return isNeedToAdd;
	};

	spreadWave( prepareFunc, processFunc );

	for ( auto& it : m_field )
	{
		if ( it.second._status == EMPTY )
		{
			it.second._cost = maxCost - it.second._cost + 1;
		}
	}

}

void ari::PathBuilderLee::spreadWave( const std::function<void( Wave & )>& prepareFunc, const std::function<bool( const Cordinate&, const Cordinate& )>& processFunc )
{
	Wave currentWave;
	Wave nextWave;

	prepareFunc( currentWave );

	//–аспространение волны
	while ( currentWave.size() != 0 )
	{
		for ( const auto & cord : currentWave )
		{
			auto neighbors = cord.get4Neighbors();
			for ( const auto& neighbor : neighbors )
			{
				if ( processFunc( cord, neighbor.second ) )
				{
					nextWave.insert( neighbor.second );
					//printWave(nextWave);
				}
			}
		}
		currentWave = nextWave;
		nextWave.clear();
	}
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
		auto neighbors = current.get4Neighbors();

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

void ari::PathBuilderLee::printWave( const Wave & wave )
{
	IDisplay_p disp = Display::create();
	disp->setColors( NS_CORE eColor::WHITE, NS_CORE eColor::BLACK );
	for ( const auto& it : wave )
		disp->print( it + Cordinate( 1, 1 ), fieldAt(it)._value % 10 + '0' );
	disp->resetColors();
	disp->print( { 0, 20 }, '>' );
	//system( "pause" );
}






















bool ari::PathBuilderLee::processWaveCell( const Cordinate& waveCell, const Cordinate& neighbor )
{
	bool isNeedToAdd = false;
			
	Cell& neighborCell = fieldAt( neighbor );
	int newValue = fieldAt( waveCell )._value + fieldAt( waveCell )._cost;


	if ( fieldAt( m_startCord )._value != 0 && newValue > fieldAt( m_startCord )._value )
	{
		isNeedToAdd = false;
	}
	else if ( neighborCell._status == START && canIFill( fieldAt( m_startCord ), newValue ) )
	{
		neighborCell._value = newValue;
		m_startCord = neighbor;
	}
	else if ( neighborCell._status == EMPTY && canIFill( neighborCell, newValue ) )
	{
		neighborCell._value = newValue;
		isNeedToAdd = true;
	}

	return isNeedToAdd;
}

bool ari::PathBuilderLee::isFieldConsist( const Cordinate& cord )
{
	return m_field.find( cord ) != m_field.end();
}

void PathBuilderLee::prepareWave( Wave &currentWave )
{
	//заполн€ем текущую волну клетками финиша
	for ( const auto& it : m_field )
	{
		if ( it.second._status == FINISH )
			currentWave.insert( it.first );
	}
}

