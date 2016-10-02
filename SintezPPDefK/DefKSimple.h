#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TKArray.h"
#include "../Libraries/TIArray.h"
#include "../Libraries/TI.h"

#include "System.h"


NS_ARI_START

class DefKSimple
{
private:

	bool										m_isCanFind;

	NS_CORE TK									findK( const NS_CORE TCode& code, const NS_CORE TK& initialKValues, const NS_CORE TI& iTarget );
	NS_CORE TK									solveSimple( System& system );
	NS_CORE TK									getKValuesFromSystem( const System & system );
	bool										isAllKValuesFinded( const System & system );

public:

	DefKSimple();

	std::pair<NS_CORE TKArray, NS_CORE TIArray>	calculate( const NS_CORE TCode& code );

};

NS_ARI_END