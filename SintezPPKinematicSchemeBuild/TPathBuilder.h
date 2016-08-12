#pragma once
#include "TKinematicScheme.h"
#include "TCordinates.h"
#include "eDirection.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class TPathBuilder
{
public:

	typedef std::vector<std::vector<int>> Field;

private:

	Field										m_field;

	int											m_start;
	int											m_finish;
	int											m_empty;
	int											m_wall;


	void										initField( const TKinematicScheme & scheme, core::TLink link );
	bool										spreadWave();
	std::vector<TCordinates>					findPath();
	TCordinates									findStartCell();
	void										printField();

public:

	TPathBuilder();
	std::vector<TCordinates>					findPath( const TKinematicScheme & scheme, core::TLink link );

};

NS_ARI_END


