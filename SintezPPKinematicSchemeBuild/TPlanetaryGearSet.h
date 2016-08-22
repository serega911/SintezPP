#pragma once

#include <vector>
#include "../Libraries/TChain.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class TPlanetaryGearSet
{
public:

	typedef std::vector<std::vector<core::TChain>> Field;

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
	NS_CORE TGearSetNumber						m_gearSetN;

	void										resetField();
	void										createTypeN( int gearSetN );
	void										createTypeDefault( int gearSetN );
	void										reverseX();
	void										reverseY();
public:

	void										print();
	void										printLine( int xPos );

	void										create( int gearSetN, Type type );

	NS_CORE TChainArray&						operator[]( int xPos );
	const NS_CORE TChainArray&					operator[]( int xPos ) const;

};

NS_ARI_END



