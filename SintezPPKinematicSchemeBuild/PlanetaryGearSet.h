#pragma once

#include <vector>
#include "../Libraries/Chain.h"
#include "../Libraries/GlobalDefines.h"
#include "../Libraries/GearSetNumber.h"
#include "../Libraries/ChainArray.h"

NS_ARI_START

class PlanetaryGearSet
{
public:

	typedef std::vector<NS_CORE ChainArray> Field;

	enum class Type
	{
		TYPE_N,
		TYPE_N_REVERSE,
		TYPE_U,
		TYPE_U_REVERSE,
		TYPE_DEFAULT
	};

	static const int							s_xSize;
	static const int							s_ySize;
	static const int							s_centerX;
	static const int							s_centerY;

private:

	Field										m_field;
	NS_CORE GearSetNumber						m_gearSetN;

	void										resetField();
	void										createTypeN( NS_CORE GearSetNumber gearSetN );
	void										createTypeDefault( NS_CORE GearSetNumber gearSetN );
	void										reverseX();
	void										reverseY();
public:

	void										print();
	void										printLine( int xPos );

	void										create( NS_CORE GearSetNumber gearSetN, Type type );

	NS_CORE ChainArray&							operator[]( int xPos );
	const NS_CORE ChainArray&					operator[]( int xPos ) const;

};

NS_ARI_END



