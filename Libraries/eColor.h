#pragma once

#include "GlobalDefines.h"

NS_CORE_START

enum class eColor
{
	BLACK
	, DARK_BLUE
	, GREEN
	, LIGHT_BLUE
	, DARK_RED
	, PURPLE
	, GOLD
	, LIGHT_GRAY
	, GRAY
	, BLUE
	, LIGHT_GREEN
	, AQUA
	, RED
	, PINK
	, YELLOW
	, WHITE
};

const eColor colors[] = { eColor::BLACK, eColor::DARK_BLUE, eColor::GREEN, eColor::LIGHT_BLUE, eColor::DARK_RED, eColor::PURPLE, eColor::GOLD,
eColor::LIGHT_GRAY, eColor::GRAY, eColor::BLUE, eColor::LIGHT_GREEN, eColor::AQUA, eColor::RED, eColor::PINK, eColor::YELLOW, eColor::WHITE };
const int colorsCount = 16;

NS_CORE_END