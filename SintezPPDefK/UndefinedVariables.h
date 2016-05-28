#pragma once

#include "Variables.h"

namespace pss
{
	class UndefinedVariables
	{
	private:

		double									m_kDefaultValue = -2.0;

		std::vector<variable>					m_kValues;

		std::vector<variable*>					m_variables;

		void									addK( );

	public:

		UndefinedVariables( std::vector<Variables> & vectVar );

		variable&								operator[]( size_t i );

	};
}