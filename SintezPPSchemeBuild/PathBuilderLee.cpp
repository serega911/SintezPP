#include<set>

#include "Display.h"
#include "PathBuilderLee.h"

NS_ARI_USING

PathBuilderLee::PathBuilderLee()
{
}

PathBuilderLee_p PathBuilderLee::create()
{
	return PathBuilderLee_p( new PathBuilderLee );
}

void PathBuilderLee::init( const size_t width, const size_t height )
{
	m_width = width;
	m_height = height;

	m_startCord = Cordinate( 0, 0 );
	isStartAchieved = false;
	//resize field
	m_field.clear();
	//create borders
	for ( int y = -1; y <= m_height; y++ )
	{
		fieldAt( Cordinate( -1, y ) )._status = WALL;
		fieldAt( Cordinate( m_width, y ) )._status = WALL;
	}
	for ( int x = 0; x < m_width; x++ )
	{
		fieldAt( Cordinate( x, -1 ) )._status = WALL;
		fieldAt( Cordinate( x, m_height ) )._status = WALL;
	}
}

std::vector<Cordinate> PathBuilderLee::run( const std::vector<ISchemeElement_p>& elements, const NS_CORE Element& start, const NS_CORE Element& finish )
{
	std::vector<Cordinate> ret;

	fillField( elements, start, finish );
	//printField();

	const PrepareWaveFunction prepareWave = [&]( Wave& wave )
	{
		//заполн€ем текущую волну клетками финиша
		for ( const auto& it : m_field )
		{
			if ( it.second._status == FINISH )
				wave.insert( it.first );
		}
	};


	const ProcessWaveCellFunction processFunc = [&]( const Cordinate& waveCell, const Cordinate& neighbor )
	{
		bool isNeedToAdd = false;

		Cell& neighborCell = fieldAt( neighbor );
		size_t newValue = fieldAt( waveCell )._value + neighborCell._cost;


		const PathBuilderLee::Cell& startCell = fieldAt( m_startCord );

		if ( isStartAchieved && newValue > startCell._value )
		{
			isNeedToAdd = false;
		}
		else if ( neighborCell._status == START && canIFill( startCell, newValue ) )
		{
			neighborCell._value = newValue;
			m_startCord = neighbor;
			isStartAchieved = true;
		}
		else if ( neighborCell._status == EMPTY && canIFill( neighborCell, newValue ) )
		{
			neighborCell._value = newValue;
			isNeedToAdd = true;
		}

		return isNeedToAdd;
	};

	spreadWave( prepareWave, processFunc );
	if ( isStartAchieved )
	{
		//printField();
		ret = findPath();
	}

	return ret;
}

void PathBuilderLee::fillField( const std::vector<ISchemeElement_p>& elements, const NS_CORE Element& start, const NS_CORE Element& finish )
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

	const PrepareWaveFunction prepareFunc = [&]( Wave& wave )
	{
		for ( const auto& it : m_field )
		{
			if ( it.second._status != EMPTY )
				wave.insert( it.first );
		}
	};


	const ProcessWaveCellFunction processFunc = [&]( const Cordinate& waveCell, const Cordinate& neighbor )
	{
		bool isNeedToAdd = false;
		if ( verifyCord( neighbor ) )
		{
			Cell& neighborCell = fieldAt( neighbor );
			if ( neighborCell._status == EMPTY && neighborCell._cost == 1 )
			{
				auto neighbours = neighbor.get4Neighbors();

				int add = 11;

				neighborCell._cost = fieldAt( waveCell )._cost + add;

				if ( add != 0 )
					maxCost = neighborCell._cost;

				isNeedToAdd = true;
			}
		}
		return isNeedToAdd;
	};

	spreadWave( prepareFunc, processFunc, true );

	for ( auto& it : m_field )
	{
		if ( it.second._status == EMPTY )
		{
			it.second._cost = maxCost - it.second._cost + 1;
		}
	}

}

void PathBuilderLee::spreadWave( const PrepareWaveFunction& prepareFunc, const ProcessWaveCellFunction& processFunc, const bool use8neigbours/* = false*/ )
{
	Wave currentWave;
	Wave nextWave;

	prepareFunc( currentWave );

	//–аспространение волны
	while ( currentWave.size() != 0 )
	{
		for ( const auto & cord : currentWave )
		{
			auto neighbors = use8neigbours ? cord.get8Neighbors() : cord.get4Neighbors();
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

std::vector<Cordinate> PathBuilderLee::findPath()
{
	// строим путь
	std::vector<Cordinate> path;
	Cordinate current = m_startCord;
	path.emplace_back( current );
	eDirection direction = eDirection::UP;

	while ( fieldAt( current )._status != FINISH )
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

bool PathBuilderLee::verifyCord( const Cordinate& cord )
{
	return cord.m_x >= 0 && cord.m_x < m_width && cord.m_y >= 0 && cord.m_y < m_height;
}

bool ari::PathBuilderLee::canIFill( const Cell& cord, const size_t value )
{
	return cord._value == 0 || value < cord._value;
}

bool PathBuilderLee::isFieldConsist( const Cordinate& cord )
{
	return m_field.find( cord ) != m_field.end();
}

PathBuilderLee::Cell& PathBuilderLee::fieldAt( const Cordinate& cord )
{
	return m_field[cord];
}

void PathBuilderLee::printField()
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
		if ( it.first.m_x >= 0 && it.first.m_y >= 0 )
			disp->print( it.first, it.second._value % 10 + '0' );
	}

	disp->resetColors();
	disp->print( { 0, 20 }, '>' );
	NS_CORE Log::pause();
}

void PathBuilderLee::printRoute( const std::vector<Cordinate> & route )
{
	IDisplay_p disp = Display::create();
	disp->setColors( NS_CORE eColor::WHITE, NS_CORE eColor::BLACK );
	for ( const auto& it : route )
		if ( it.m_x >= 0 && it.m_y >= 0 )
			disp->print( it, '#' );
	disp->resetColors();
	disp->print( { 0, 20 }, '>' );
	//NS_CORE Log::pause();
}

void PathBuilderLee::printWave( const Wave & wave )
{
	IDisplay_p disp = Display::create();
	disp->setColors( NS_CORE eColor::WHITE, NS_CORE eColor::BLACK );
	for ( const auto& it : wave )
		if ( it.m_x >= 0 && it.m_y >= 0 )
			disp->print( it, fieldAt( it )._cost % 10 + '0' );
	disp->resetColors();
	disp->print( { 0, 20 }, '>' );
	//NS_CORE Log::pause();
}
