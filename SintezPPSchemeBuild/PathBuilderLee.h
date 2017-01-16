#pragma once

#include <map>
#include <set>
#include <functional>

#include "IPathBuildStartegy.h"

NS_ARI_START

class PathBuilderLee;

typedef std::shared_ptr<PathBuilderLee> PathBuilderLee_p;

class PathBuilderLee: public IPathBuildStartegy
{
private:
			
	enum eCellStatus
	{
		EMPTY,
		START,
		FINISH,
		WALL
	};

	struct Cell
	{
		size_t		_value = 0;
		size_t		_cost = 1;
		eCellStatus	_status = EMPTY;
	};

	typedef std::map<Cordinate, Cell> Field;
	typedef std::set<Cordinate> Wave;

	Field										m_field;
	int											m_width;
	int											m_height;
	
	Cordinate									m_startCord;

	PathBuilderLee();

	void										printField();
	void										printRoute( const std::vector<Cordinate> & route);
	void										printWave( const Wave & route );

	bool										verifyCord( const Cordinate& cord );
	bool										canIFill( const Cell& cord, const int value );
	Cell&										fieldAt( const Cordinate& cord );
	bool										isFieldConsist( const Cordinate& cord );

	void										fillField( const std::vector<ISchemeElement_p>& elements, NS_CORE Element& start, NS_CORE Element& finish );
	void										spreadWave( const std::function<void( Wave & )>& prepareFunc, const std::function<bool( const Cordinate& , const Cordinate& )>& processFunc );

	bool										processWaveCell( const Cordinate& waveCell, const Cordinate& neighbor );
	void										prepareWave( Wave &currentWave );
	

	std::vector<Cordinate>						findPath();


public:

	static PathBuilderLee_p						create();

	virtual void								init( const size_t width, const size_t height ) override;
	virtual std::vector<Cordinate>				run( const std::vector<ISchemeElement_p>& elements, NS_CORE Element& start, NS_CORE Element& finish ) override;

};



NS_ARI_END