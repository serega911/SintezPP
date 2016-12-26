#pragma once

#include <vector>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/eMainElement.h"

#include "Cordinate.h"

NS_ARI_START

class GearSet
{
private:

	struct Cell
	{
		NS_CORE eMainElement	_element;
		Cordinate				_cord;
	};

	typedef std::vector<Cell> Cordinates;
	friend class GearSetFactory;

	Cordinate									m_anchor;
	Cordinates									m_cords;

	GearSet();
	void										addCord( const Cordinate& cord, NS_CORE eMainElement elem);

public:
	
	void										setAnchor( const Cordinate& cord );

	const Cordinate&							getAnchor() const;
	const Cordinates&							get() const;

	~GearSet();
};

NS_ARI_END

