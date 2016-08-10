#pragma once
#include<vector>

#include "../Libraries/TChain.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

class TPlanetaryGearSet
{
public:
	enum ePlanetarySetType {
		DEFAULT
		, P_NORMAL
		, U_NORMAL
		, P_INVERSE
		, U_INVERSE
	};

	TPlanetaryGearSet(ePlanetarySetType t = DEFAULT);
	~TPlanetaryGearSet(void);

	void Create( NS_CORE TGearSetNumber Num, ePlanetarySetType t = DEFAULT );
	void Invers(int Num);

	size_t getXMAX();
	size_t getYMAX();

	NS_CORE TChain getCellMas( size_t i, size_t j );

	std::vector<NS_CORE TChain>getMas( size_t i );

private:

	static const size_t							s_mapWidth;
	static const size_t							s_mapHeight;
	static const NS_CORE TChain					s_emptyChain;

	ePlanetarySetType							m_limitType;
	std::vector<std::vector<NS_CORE TChain>>	m_map;

	void MakeLimits(ePlanetarySetType t);

};

NS_ARI_END