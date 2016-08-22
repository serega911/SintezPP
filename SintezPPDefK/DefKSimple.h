#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"

#include "System.h"


NS_ARI_START

class DefKSimple
{
private:

	NS_CORE TK									findK( const NS_CORE TCode& code, const NS_CORE TK& initialKValues, const NS_CORE TI& iTarget );
	NS_CORE TK									solveSimple( System& system );
	NS_CORE TK									getKValuesFromSystem( const System & system );

public:

	NS_CORE TK									calculate( const NS_CORE TCode& code );

};

NS_ARI_END