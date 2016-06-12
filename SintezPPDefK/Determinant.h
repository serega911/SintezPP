#pragma once

#include <vector>

#include "Fumction.h"

namespace pss
{
	class Determinant
	{
	private:
		size_t									m_size;
		std::vector<std::vector<Equation>>		m_determinant;
	public:

		Determinant();

		void									setSize( size_t size );
		void									setEquation( size_t i, size_t j, const Equation & eq );

		const std::vector<Equation>&			operator[]( size_t i );

	};
}