#pragma once

#include "GlobalDefines.h"

NS_CORE_START

struct KinematicSchemeData
{
	size_t	_radialRoads;
	size_t	_axialRoads;

	KinematicSchemeData( const size_t radial, const size_t axial )
		: _radialRoads(radial), _axialRoads(axial) {}

	KinematicSchemeData()
		: _radialRoads( 0 ), _axialRoads( 0 ) {}

	static const KinematicSchemeData s_empty;

	bool operator!=( const KinematicSchemeData& obj ) const
	{
		return obj._axialRoads != _axialRoads || obj._radialRoads != _radialRoads;
	}

};

__declspec( selectany ) const KinematicSchemeData KinematicSchemeData::s_empty = KinematicSchemeData( 0, 0 );



NS_CORE_END