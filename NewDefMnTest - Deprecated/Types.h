#pragma once

#include <map>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Element.h"

NS_ARI_START

typedef std::pair<NS_CORE Element, double>	Minit;
typedef std::map<NS_CORE Element, double>	M;
typedef std::map<NS_CORE Element, double>	W;
typedef std::map<NS_CORE Element, char>	N;

const NS_CORE GearSetNumber setN( 1 );
const NS_CORE Element sun = NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, setN );
const NS_CORE Element epy = NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, setN );
const NS_CORE Element car = NS_CORE Element( NS_CORE eMainElement::CARRIER, setN );
const NS_CORE Element in2 = NS_CORE Element( NS_CORE eMainElement::INPUT, setN );

NS_ARI_END