#pragma once

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
		WALL,
		ADJOINED,
	};

	struct Cell
	{
		size_t		_value = 0;
		eCellStatus	_status = EMPTY;
	};

	typedef std::vector<std::vector<Cell>> Field;

	Field										m_field;
	size_t										m_width;
	size_t										m_height;
	
	Cordinate									m_startCord;

	PathBuilderLee();
	void										printField();
	bool										verifyCord( const Cordinate& cord );
	void										fillField( const std::vector<ISchemeElement_p>& elements, NS_CORE Element& start, NS_CORE Element& finish );
	Cell&										fieldAt( const Cordinate& cord );
	bool										spreadWave();
	std::vector<Cordinate>						findPath();

public:

	static PathBuilderLee_p						create();

	virtual void								init( const size_t width, const size_t height ) override;

	virtual std::vector<Cordinate>				run( const std::vector<ISchemeElement_p>& elements, NS_CORE Element& start, NS_CORE Element& finish ) override;

};



NS_ARI_END