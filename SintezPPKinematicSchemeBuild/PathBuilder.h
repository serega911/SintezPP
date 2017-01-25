#pragma once
#include "KinematicScheme.h"
#include "Cordinates.h"
#include "eDirection.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class PathBuilder
{
public:

	typedef std::vector<std::vector<int>> Field;

private:

	Field										m_field;

	int											m_start;
	int											m_finish;
	int											m_empty;
	int											m_wall;


	void										initField( const KinematicScheme & scheme, core::Link link );
	bool										spreadWave();
	TCordinatesArray							findPath();
	Cordinate									findStartCell();
	void										printField();

 	bool										checkIsNear( const Cordinate& cord, const int elem );

	void										addRestrictions();

public:

	PathBuilder();
	TCordinatesArray							findPath( const KinematicScheme & scheme, core::Link link );

};

NS_ARI_END


