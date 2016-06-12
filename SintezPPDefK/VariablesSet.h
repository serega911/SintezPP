#pragma once

#include "../Libraries/GlobalDefines.h"

#include "Variable.h"
#include "../Libraries/eMainElement.h"

#include <map>


NS_PSS_START

class VariablesSet
{
private:

	std::map<eMainElement, Variable>			m_set;

public:

	Variable&									operator[]( const eMainElement & element );
	const Variable&								operator[]( const eMainElement & element ) const;

};

NS_PSS_END