#pragma once
#include "UserDefinedTypesMacros.h"
#include <vector>
#include "eMainElement.h"

NS_CORE_START

typedef std::vector<eMainElement> eMainElementArray;
//USER_DEFINED_TYPE_VECTOR( eMainElementArray, std::vector, eMainElement )

NS_CORE_END