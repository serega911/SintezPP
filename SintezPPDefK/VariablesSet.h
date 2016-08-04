#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Variable.h"
#include "../Libraries/eMainElement.h"

#include <map>


NS_ARI_START

class VariablesSet
{
private:

	std::map<NS_CORE eMainElement, Variable>	m_set;

public:

	Variable&									operator[]( const NS_CORE eMainElement & element );
	const Variable&								operator[]( const NS_CORE eMainElement & element ) const;

};

NS_ARI_END