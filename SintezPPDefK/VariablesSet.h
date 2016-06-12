#pragma once

#include "Variable.h"
#include "../Libraries/eMainElement.h"

#include <map>

namespace pss
{
	class VariablesSet
	{
	private:

		std::map<eMainElement, Variable>		m_set;

	public:

		Variable&								operator[]( const eMainElement & element );
		const Variable&							operator[]( const eMainElement & element ) const;

	};

}