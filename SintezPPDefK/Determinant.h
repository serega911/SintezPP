#pragma once

#include "../Libraries/GlobalDefines.h"

#include <vector>

#include "Defines.h"

NS_PSS_START

class Determinant
{
private:
	size_t										m_size;
	std::vector<std::vector<Equation>>			m_determinant;
public:

	Determinant();

	void										setSize( size_t size );
	void										setEquation( size_t i, size_t j, const Equation & eq );

	const std::vector<Equation>&				operator[]( size_t i );

};

NS_PSS_END